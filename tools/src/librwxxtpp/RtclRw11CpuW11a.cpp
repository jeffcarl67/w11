// $Id: RtclRw11CpuW11a.cpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013- by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2013-02-16   488   1.0    Initial version
// 2013-02-02   480   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation of RtclRw11CpuW11a.
*/

#include <iostream>

#include "RtclRw11CpuW11a.hpp"

using namespace std;

/*!
  \class Retro::RtclRw11CpuW11a
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Constructor

RtclRw11CpuW11a::RtclRw11CpuW11a(Tcl_Interp* interp, const char* name)
  : RtclRw11CpuBase<Rw11CpuW11a>(interp, name, "Rw11CpuW11a")
{
  SetupGetSet();
}

//------------------------------------------+-----------------------------------
//! Destructor

RtclRw11CpuW11a::~RtclRw11CpuW11a()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

void RtclRw11CpuW11a::SetupGetSet()
{
  RtclRw11Cpu::SetupGetSet();
  return;
}

} // end namespace Retro
