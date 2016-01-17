/*
Copyright (c) 2014, Trail of Bits
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Trail of Bits nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef LLVMOBJECTTARGET_H
#define LLVMOBJECTTARGET_H

#include <vector>
#include <string>
#include <list>
#include <map>

#include "bincomm.h"


class LLVMObjectTarget : public ExecutableContainer {
  std::string                    mod_name;
  //(a, b) -- a is offset to apply to base of secT to get its real base
  //len remainds the same

  llvm::object::ObjectFile    *objectfile;
  VA                        baseAddr;
  VA                        extent;
public:
  typedef std::pair<uint64_t, llvm::object::SectionRef>  secT;

  virtual ~LLVMObjectTarget(void);
  virtual bool is_open(void);
  virtual bool get_exports(std::list<std::pair<std::string, VA> > &);
  virtual bool find_import_name(uint32_t, std::string &);
  virtual bool is_addr_relocated(uint32_t);
  virtual bool relocate_addr(VA, VA &, VA &);
  virtual bool get_sections(std::vector<SectionDesc>  &);
  virtual std::string name(void) { return this->mod_name; }


  virtual ::uint64_t getBase(void) const;
  virtual ::uint64_t getExtent(void) const;
  virtual int readByte(::uint64_t, uint8_t *) const;
  virtual bool getEntryPoint(::uint64_t &ep) const;
  virtual llvm::object::SectionRef fixRelocationSection(const llvm::object::SectionRef &sec);

protected:
  std::vector<secT>              secs;
  std::string                    hash;
  std::map<llvm::object::SectionRef, llvm::object::SectionRef> wheres_my_relo;

  LLVMObjectTarget(const std::string &modname, llvm::object::ObjectFile *of);

private:
    LLVMObjectTarget();
    void populateReloMap(const llvm::object::SectionRef &sr);

};

bool getSectionForAddr(const std::vector<LLVMObjectTarget::secT> &secs, 
        uint32_t addr, 
        llvm::object::SectionRef &secref,
        uint32_t &offt);

#endif
