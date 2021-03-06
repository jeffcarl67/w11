// $Id: RlinkCommand.hpp 1185 2019-07-12 17:29:12Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2011-2019 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2019-03-10  1121   1.4.3  add BlockDoneAll()
// 2018-12-24  1092   1.4.2  rename IsBlockExt -> HasBlockExt
// 2018-12-23  1091   1.4.1  CmdWblk(),SetBlockWrite(): add move version
// 2018-12-01  1076   1.4    use unique_ptr
// 2017-04-07   868   1.3.2  Dump(): add detail arg
// 2017-03-11   859   1.3.1  add CommandInfo()
// 2015-04-02   661   1.3    expect logic: add stat check, Print() without cntx
// 2014-12-21   617   1.2.2  use kStat_M_RbTout for rbus timeout
// 2014-12-20   616   1.2.1  add kFlagChkDone
// 2014-12-06   609   1.2    new rlink v4 iface
// 2013-05-06   495   1.0.1  add RlinkContext to Print() args; drop oper<<()
// 2011-03-27   374   1.0    Initial version
// 2011-01-09   354   0.1    First draft
// ---------------------------------------------------------------------------


/*!
  \brief   Declaration of class RlinkCommand.
*/

#ifndef included_Retro_RlinkCommand
#define included_Retro_RlinkCommand 1

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <ostream>
#include <memory>

#include "librtools/Rtools.hpp"

#include "RlinkContext.hpp"
#include "RlinkAddrMap.hpp"
#include "RlinkCommandExpect.hpp"

#include "librtools/Rbits.hpp"

namespace Retro {

  class RlinkCommand : public Rbits {
    public:
      typedef std::unique_ptr<RlinkCommandExpect>  exp_uptr_t;

                    RlinkCommand();
                    RlinkCommand(const RlinkCommand& rhs);
                   ~RlinkCommand();
 
      void          CmdRreg(uint16_t addr);
      void          CmdRblk(uint16_t addr, size_t size);
      void          CmdRblk(uint16_t addr, uint16_t* pblock, size_t size);
      void          CmdWreg(uint16_t addr, uint16_t data);
      void          CmdWblk(uint16_t addr, const std::vector<uint16_t>& block);
      void          CmdWblk(uint16_t addr, std::vector<uint16_t>&& block);
      void          CmdWblk(uint16_t addr, const uint16_t* pblock, size_t size);
      void          CmdLabo();
      void          CmdAttn();
      void          CmdInit(uint16_t addr, uint16_t data);

      void          SetCommand(uint8_t cmd, uint16_t addr=0, uint16_t data=0);
      void          SetSeqNumber(uint8_t snum);   
      void          SetAddress(uint16_t addr);
      void          SetData(uint16_t data);
      void          SetBlockWrite(const std::vector<uint16_t>& block);
      void          SetBlockWrite(std::vector<uint16_t>&& block);
      void          SetBlockRead(size_t size) ;
      void          SetBlockExt(uint16_t* pblock, size_t size);
      void          SetBlockDone(uint16_t dcnt);
      void          SetStatus(uint8_t stat);
      void          SetFlagBit(uint32_t mask);
      void          ClearFlagBit(uint32_t mask);
      void          SetRcvSize(size_t rsize);

      void          SetExpect(exp_uptr_t&& upexp);
      RlinkCommandExpect&  EnsureExpect();
      void          SetExpectStatus(uint8_t stat, uint8_t statmsk=0xff);
      void          SetExpectStatusDefault(uint8_t stat=0, uint8_t statmsk=0x0);

      uint8_t       Request() const;
      uint8_t       Command() const;
      uint8_t       SeqNumber() const;
      uint16_t      Address() const;
      uint16_t      Data() const;
      const std::vector<uint16_t>& Block() const;
      bool          HasBlockExt() const;
      uint16_t*        BlockPointer();
      const uint16_t*  BlockPointer() const;
      size_t        BlockSize() const;
      size_t        BlockDone() const;
      bool          BlockDoneAll() const;
      uint8_t       Status() const;
      uint32_t      Flags() const;
      bool          TestFlagAny(uint32_t mask) const;
      bool          TestFlagAll(uint32_t mask) const;
      size_t        RcvSize() const;

      bool          HasExpect() const;
      const RlinkCommandExpect& Expect() const;
      uint8_t       ExpectStatusValue() const;
      uint8_t       ExpectStatusMask() const;
      bool          ExpectStatusSet() const;
      bool          StatusCheck() const;
      bool          StatusIsChecked() const;

      void          Print(std::ostream& os, const RlinkAddrMap* pamap=0, 
                          size_t abase=16, size_t dbase=16, 
                          size_t sbase=16) const;
      std::string   CommandInfo() const;
      void          Dump(std::ostream& os, int ind=0, const char* text=0,
                         int detail=0) const;

      static const char* CommandName(uint8_t cmd);
      static const RflagName* FlagNames();

      RlinkCommand& operator=(const RlinkCommand& rhs);

    // some constants (also defined in cpp)
      static const uint8_t  kCmdRreg = 0;   //!< command code read register
      static const uint8_t  kCmdRblk = 1;   //!< command code read block
      static const uint8_t  kCmdWreg = 2;   //!< command code write register
      static const uint8_t  kCmdWblk = 3;   //!< command code write block
      static const uint8_t  kCmdLabo = 4;   //!< command code list abort
      static const uint8_t  kCmdAttn = 5;   //!< command code get attention
      static const uint8_t  kCmdInit = 6;   //!< command code send initialize

      static const uint32_t kFlagInit   = 1u<<0;  //!< cmd,addr,data setup
      static const uint32_t kFlagSend   = 1u<<1;  //!< command send
      static const uint32_t kFlagDone   = 1u<<2;  //!< command done
      static const uint32_t kFlagLabo   = 1u<<3;  //!< command labo'ed

      static const uint32_t kFlagPktBeg = 1u<<4;  //!< command first in packet
      static const uint32_t kFlagPktEnd = 1u<<5;  //!< command last in packet

      static const uint32_t kFlagErrNak = 1u<<8;  //!< error: nak abort
      static const uint32_t kFlagErrDec = 1u<<9;  //!< error: decode error

      static const uint32_t kFlagChkStat= 1u<<12; //!< stat expect check failed
      static const uint32_t kFlagChkData= 1u<<13; //!< data expect check failed
      static const uint32_t kFlagChkDone= 1u<<14; //!< done expect check failed

      static const uint8_t  kStat_M_Stat   = 0xf0; //!< stat: external stat bits
      static const uint8_t  kStat_V_Stat   = 4; 
      static const uint8_t  kStat_B_Stat   = 0x0f; 
      static const uint8_t  kStat_M_Attn   = kBBit03;//!< stat: attn   flag set
      static const uint8_t  kStat_M_RbTout = kBBit02;//!< stat: rbtout flag set
      static const uint8_t  kStat_M_RbNak  = kBBit01;//!< stat: rbnak  flag set
      static const uint8_t  kStat_M_RbErr  = kBBit00;//!< stat: rberr  flag set

    protected: 
      void          SetCmdSimple(uint8_t cmd, uint16_t addr, uint16_t data);

    protected: 
      uint8_t       fRequest;               //!< rlink request (cmd+seqnum)
      uint16_t      fAddress;               //!< rbus address
      uint16_t      fData;                  //!< data 
      std::vector<uint16_t> fBlock;         //!< data vector for blk commands 
      uint16_t*     fpBlockExt;             //!< external data for blk commands
      size_t        fBlockExtSize;          //!< transfer size if data external
      size_t        fBlockDone;             //!< valid transfer count
      uint8_t       fStatus;                //!< rlink command status
      uint32_t      fFlags;                 //!< state bits
      size_t        fRcvSize;               //!< receive size for command
      bool          fExpectStatusSet;       //!< stat chk set explicitely
      uint8_t       fExpectStatusVal;       //!< status value
      uint8_t       fExpectStatusMsk;       //!< status mask
      exp_uptr_t    fupExpect;              //!< pointer to expect container
  };
  
} // end namespace Retro

#include "RlinkCommand.ipp"

#endif
