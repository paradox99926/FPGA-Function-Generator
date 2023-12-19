// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Wed Nov 29 19:50:46 2023
// Host        : LAPTOP-LRASCO7O running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub {C:/Users/ROG strix/Desktop/FPGA-Function
//               Generator/DDS_function_generator/DDS_function_generator.srcs/sources_1/ip/PLL/PLL_stub.v}
// Design      : PLL
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tfgg484-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module PLL(clk_out1, resetn, locked, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="clk_out1,resetn,locked,clk_in1" */;
  output clk_out1;
  input resetn;
  output locked;
  input clk_in1;
endmodule
