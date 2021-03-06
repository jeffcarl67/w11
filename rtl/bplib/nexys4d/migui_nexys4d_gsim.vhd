-- $Id: migui_nexys4d_gsim.vhd 1201 2019-08-10 16:51:22Z mueller $
-- SPDX-License-Identifier: GPL-3.0-or-later
-- Copyright 2018- by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
-- 
------------------------------------------------------------------------------
-- Module Name:    migui_nexys4d - sim
-- Description:    MIG generated for nexys4d - simple simulator
--
-- Dependencies:   bplib/mig/migui_core_gsim
-- Test bench:     tb_tst_sram_nexys4d
-- Target Devices: arty board
-- Tool versions:  viv 2017.2; ghdl 0.34
--
-- Revision History: 
-- Date         Rev Version  Comment
-- 2018-12-30  1099   1.0    Initial version (cloned from arty)
-- 
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.slvtypes.all;
use work.miglib.all;
use work.miglib_nexys4d.all;

entity migui_nexys4d is                 -- MIG generated for nexys4d
  port (
    DDR2_DQ      : inout slv16;         -- dram: data in/out
    DDR2_DQS_P   : inout slv2;          -- dram: data strobe (diff-p)
    DDR2_DQS_N   : inout slv2;          -- dram: data strobe (diff-n)
    DDR2_ADDR    : out   slv13;         -- dram: address
    DDR2_BA      : out   slv3;          -- dram: bank address
    DDR2_RAS_N   : out   slbit;         -- dram: row addr strobe    (act.low)
    DDR2_CAS_N   : out   slbit;         -- dram: column addr strobe (act.low)
    DDR2_WE_N    : out   slbit;         -- dram: write enable       (act.low)
    DDR2_CK_P    : out   slv1;          -- dram: clock (diff-p)
    DDR2_CK_N    : out   slv1;          -- dram: clock (diff-n)
    DDR2_CKE     : out   slv1;          -- dram: clock enable
    DDR2_CS_N    : out   slv1;          -- dram: chip select        (act.low)
    DDR2_DM      : out   slv2;          -- dram: data input mask
    DDR2_ODT     : out   slv1;          -- dram: on-die termination
    APP_ADDR            : in  slv(mig_mawidth-1 downto 0); -- MIGUI address
    APP_CMD             : in  slv3;     -- MIGUI command
    APP_EN              : in  slbit;    -- MIGUI command enable
    APP_WDF_DATA        : in  slv(mig_dwidth-1 downto 0);-- MIGUI write data
    APP_WDF_END         : in  slbit;                     -- MIGUI write end
    APP_WDF_MASK        : in  slv(mig_mwidth-1 downto 0); -- MIGUI write mask
    APP_WDF_WREN        : in  slbit;      -- MIGUI data write enable
    APP_RD_DATA         : out slv(mig_dwidth-1 downto 0); -- MIGUI read data
    APP_RD_DATA_END     : out slbit;                      -- MIGUI read end
    APP_RD_DATA_VALID   : out slbit;                      -- MIGUI read valid
    APP_RDY             : out slbit;    -- MIGUI ready for cmd
    APP_WDF_RDY         : out slbit;    -- MIGUI ready for data write
    APP_SR_REQ          : in  slbit;    -- MIGUI reserved (tie to 0)
    APP_REF_REQ         : in  slbit;    -- MIGUI refresh request
    APP_ZQ_REQ          : in  slbit;    -- MIGUI ZQ calibrate request
    APP_SR_ACTIVE       : out slbit;    -- MIGUI reserved (ignore)
    APP_REF_ACK         : out slbit;    -- MIGUI refresh acknowledge
    APP_ZQ_ACK          : out slbit;    -- MIGUI ZQ calibrate acknowledge
    UI_CLK              : out slbit;    -- MIGUI clock
    UI_CLK_SYNC_RST     : out slbit;    -- MIGUI reset
    INIT_CALIB_COMPLETE : out slbit;    -- MIGUI inital calibration complete
    SYS_CLK_I           : in  slbit;    -- MIGUI system clock
    CLK_REF_I           : in  slbit;    -- MIGUI reference clock
    DEVICE_TEMP_I       : in  slv12;    -- MIGUI xadc temperature
    SYS_RST             : in  slbit     -- MIGUI system reset
  );
end migui_nexys4d;


architecture sim of migui_nexys4d is
  
begin

  -- On Nexys4 we have
  --   SYS_CLK_I   100 Mhz
  --   controller  300 MHz
  --   UI_CLK       75 MHz   (4:1)
  -- therefore for simulation
  --   f_vco    1200 MHz
  --   --> mul  12        (f_vco/SYS_CLK)
  --   --> div  16        (f_vco/UI_CLK)
  
  MIG_SIM : migui_core_gsim
    generic map (
      BAWIDTH => mig_bawidth,
      MAWIDTH => mig_mawidth,
      SAWIDTH => 24,
      CLKMUI_MUL => 12,
      CLKMUI_DIV => 16)
    port map (
      SYS_CLK             => SYS_CLK_I,
      SYS_RST             => SYS_RST,
      UI_CLK              => UI_CLK,
      UI_CLK_SYNC_RST     => UI_CLK_SYNC_RST,
      INIT_CALIB_COMPLETE => INIT_CALIB_COMPLETE,
      APP_RDY             => APP_RDY,
      APP_EN              => APP_EN,
      APP_CMD             => APP_CMD,
      APP_ADDR            => APP_ADDR,
      APP_WDF_RDY         => APP_WDF_RDY,
      APP_WDF_WREN        => APP_WDF_WREN,
      APP_WDF_DATA        => APP_WDF_DATA,
      APP_WDF_MASK        => APP_WDF_MASK,
      APP_WDF_END         => APP_WDF_END,
      APP_RD_DATA_VALID   => APP_RD_DATA_VALID,
      APP_RD_DATA         => APP_RD_DATA,
      APP_RD_DATA_END     => APP_RD_DATA_END,
      APP_REF_REQ         => APP_REF_REQ,
      APP_ZQ_REQ          => APP_ZQ_REQ,
      APP_REF_ACK         => APP_REF_ACK,
      APP_ZQ_ACK          => APP_ZQ_ACK
    );

    DDR2_DQ      <= (others=>'Z');
    DDR2_DQS_P   <= (others=>'Z');
    DDR2_DQS_N   <= (others=>'Z');
    DDR2_ADDR    <= (others=>'0');
    DDR2_BA      <= (others=>'0');
    DDR2_RAS_N   <= '1';
    DDR2_CAS_N   <= '1';
    DDR2_WE_N    <= '1';
    DDR2_CK_P    <= (others=>'0');
    DDR2_CK_N    <= (others=>'1');
    DDR2_CKE     <= (others=>'0');
    DDR2_CS_N    <= (others=>'1');
    DDR2_DM      <= (others=>'0');
    DDR2_ODT     <= (others=>'0');
  
    APP_SR_ACTIVE       <= '0';

end sim;
