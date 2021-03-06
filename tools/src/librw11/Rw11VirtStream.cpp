// $Id: Rw11VirtStream.cpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2019 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2019-04-14  1131   1.1.2  add Error(),Eof()
// 2018-12-19  1090   1.1.1  use RosPrintf(bool)
// 2018-12-02  1076   1.1    use unique_ptr for New()
// 2017-04-07   868   1.0.3  Dump(): add detail arg
// 2017-04-02   864   1.0.2  signal for input streams WProt
// 2013-05-05   516   1.0.1  Open(): support ?app and ?bck=n options
// 2013-05-04   515   1.0    Initial version
// 2013-05-01   513   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation of Rw11VirtStream.
*/
#include <memory>

#include "librtools/Rtools.hpp"
#include "librtools/Rexception.hpp"
#include "librtools/RparseUrl.hpp"
#include "librtools/RosFill.hpp"
#include "librtools/RosPrintf.hpp"

#include "Rw11VirtStream.hpp"

using namespace std;

/*!
  \class Retro::Rw11VirtStream
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Default constructor

Rw11VirtStream::Rw11VirtStream(Rw11Unit* punit)
  : Rw11Virt(punit),
    fIStream(false),
    fOStream(false),
    fFile(0)
{
  fStats.Define(kStatNVSRead,    "NVSRead",     "Read() calls");
  fStats.Define(kStatNVSReadByt, "NVSReadByt",  "bytes read");
  fStats.Define(kStatNVSWrite,   "NVSWrite",    "Write() calls");
  fStats.Define(kStatNVSWriteByt,"NVSWriteByt", "bytes written");
  fStats.Define(kStatNVSFlush,   "NVSFlush",    "Flush() calls");
  fStats.Define(kStatNVSTell,    "NVSTell",     "Tell() calls");
  fStats.Define(kStatNVSSeek,    "NVSSeek",     "Seek() calls");
}

//------------------------------------------+-----------------------------------
//! Destructor

Rw11VirtStream::~Rw11VirtStream()
{
  if (fFile) ::fclose(fFile);
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Open(const std::string& url, RerrMsg& emsg)
{
  RparseUrl  opts;
  if (!opts.Set(fpUnit->AttachOpts(), "|ronly|wonly|", emsg)) return false;
  fIStream = opts.FindOpt("ronly");
  fOStream = opts.FindOpt("wonly");
  if (!(fIStream ^ fOStream)) 
    throw Rexception("Rw11VirtStream::Open", 
                     "Bad state: neither ronly nor wonly seen");

  if (fOStream) {                           // handle output streams
    if (!fUrl.Set(url, "|app|bck=|", emsg)) return false;
    if (!Rtools::CreateBackupFile(fUrl, emsg)) return false;
        
    fFile = ::fopen(fUrl.Path().c_str(), fUrl.FindOpt("app") ? "a" : "w");

  } else {                                  // handle input  streams
    fWProt = true;
    if (!fUrl.Set(url, "", emsg)) return false;
    fFile = ::fopen(fUrl.Path().c_str(), "r");
  }

  if (!fFile) {
    emsg.InitErrno("Rw11VirtStream::Open()", 
                   string("fopen() for '") + fUrl.Path() + "' failed: ",
                   errno);
    return false;
  }

  return true;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

int Rw11VirtStream::Read(uint8_t* data, size_t count, RerrMsg& emsg)
{
  if (!fIStream)
    throw Rexception("Rw11VirtStream::Read", 
                     "Bad state: Read() called but fIStream=false");
  if (!fFile) 
    throw Rexception("Rw11VirtStream::Read", "Bad state: file not open");

  fStats.Inc(kStatNVSRead);
  size_t irc = ::fread(data, 1, count, fFile);
  if (irc == 0 && ::ferror(fFile)) {
    emsg.InitErrno("Rw11VirtStream::Read()", "fread() failed: ", errno);
    return -1;
  }
  
  fStats.Inc(kStatNVSReadByt, double(irc));
  return int(irc);
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Write(const uint8_t* data, size_t count, RerrMsg& emsg)
{
  if (!fOStream)
    throw Rexception("Rw11VirtStream::Write", 
                     "Bad state: Write() called but fOStream=false");
  if (!fFile) 
    throw Rexception("Rw11VirtStream::Write", "Bad state: file not open");

  fStats.Inc(kStatNVSWrite);
  size_t irc = ::fwrite(data, 1, count, fFile);
  if (irc != count) {
    emsg.InitErrno("Rw11VirtStream::Write()", "fwrite() failed: ", errno);
    return false;
  }

  fStats.Inc(kStatNVSWriteByt, double(count));
  return true;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Flush(RerrMsg& emsg)
{
  if (!fOStream) return true;
  if (!fFile) 
    throw Rexception("Rw11VirtStream::Write", "Bad state: file not open");

  fStats.Inc(kStatNVSFlush);
  size_t irc = ::fflush(fFile);
  if (irc != 0) {
    emsg.InitErrno("Rw11VirtStream::Flush()", "fflush() failed: ", errno);
    return false;
  }

  return true;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

int Rw11VirtStream::Tell(RerrMsg& emsg)
{
  if (!fFile) 
    throw Rexception("Rw11VirtStream::Tell", "Bad state: file not open");

  fStats.Inc(kStatNVSTell);
  long irc = ::ftell(fFile);
  if (irc < 0) {
    emsg.InitErrno("Rw11VirtStream::Tell()", "ftell() failed: ", errno);
    return -1;
  }

  return int(irc);
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Seek(int pos, RerrMsg& emsg)
{
  if (!fFile) 
    throw Rexception("Rw11VirtStream::Seek", "Bad state: file not open");

  fStats.Inc(kStatNVSSeek);
  int whence = SEEK_SET;
  if (pos < 0) {
    pos = 0;
    whence = SEEK_END;
  }
  int irc = ::fseek(fFile, pos, whence);

  if (irc < 0) {
    emsg.InitErrno("Rw11VirtStream::Seek()", "fseek() failed: ", errno);
    return false;
  }

  return true;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Error() const
{
  return fFile ? ::ferror(fFile) : true;
}
  
//------------------------------------------+-----------------------------------
//! FIXME_docs

bool Rw11VirtStream::Eof() const
{
  return fFile ? ::feof(fFile) : true;
}
  
//------------------------------------------+-----------------------------------
//! FIXME_docs

void Rw11VirtStream::Dump(std::ostream& os, int ind, const char* text,
                          int detail) const
{
  RosFill bl(ind);
  os << bl << (text?text:"--") << "Rw11VirtStream @ " << this << endl;

  os << bl << "  fIStream:        " << RosPrintf(fIStream) << endl;
  os << bl << "  fOStream:        " << RosPrintf(fOStream) << endl;
  os << bl << "  fFile:           " << fFile << endl;
  if (fFile) {
    os << bl << "  fFile.tell       " << ::ftell(fFile) << endl;
    os << bl << "  fFile.error      " << ::ferror(fFile) << endl;
    os << bl << "  fFile.eof        " << ::feof(fFile) << endl;
  }
  
  Rw11Virt::Dump(os, ind, " ^", detail);
  return;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

std::unique_ptr<Rw11VirtStream> Rw11VirtStream::New(const std::string& url,
                                                    Rw11Unit* punit,
                                                    RerrMsg& emsg)
{
  unique_ptr<Rw11VirtStream> up;
  up.reset(new Rw11VirtStream(punit));
  if (!up->Open(url, emsg)) up.reset();
  return up;
}


} // end namespace Retro
