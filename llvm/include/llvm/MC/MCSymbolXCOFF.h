//===- MCSymbolXCOFF.h -  ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_MC_MCSYMBOLXCOFF_H
#define LLVM_MC_MCSYMBOLXCOFF_H

#include "llvm/ADT/Optional.h"
#include "llvm/BinaryFormat/XCOFF.h"
#include "llvm/MC/MCSymbol.h"

namespace llvm {

class MCSymbolXCOFF : public MCSymbol {
public:
  MCSymbolXCOFF(const StringMapEntry<bool> *Name, bool isTemporary)
      : MCSymbol(SymbolKindXCOFF, Name, isTemporary) {}

  static bool classof(const MCSymbol *S) { return S->isXCOFF(); }

  void setStorageClass(XCOFF::StorageClass SC) {
    assert((!StorageClass.hasValue() || StorageClass.getValue() == SC) &&
           "Redefining StorageClass of XCOFF MCSymbol.");
    StorageClass = SC;
  };

  XCOFF::StorageClass getStorageClass() const {
    assert(StorageClass.hasValue() &&
           "StorageClass not set on XCOFF MCSymbol.");
    return StorageClass.getValue();
  }

private:
  Optional<XCOFF::StorageClass> StorageClass;
};

} // end namespace llvm

#endif // LLVM_MC_MCSYMBOLXCOFF_H
