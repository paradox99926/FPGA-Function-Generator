// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Sat Dec  2 11:33:08 2023
// Host        : LAPTOP-LRASCO7O running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub {c:/Users/ROG strix/Desktop/FPGA-Function
//               Generator/DDS_function_generator/DDS_function_generator.srcs/sources_1/ip/mult_gen_0/mult_gen_0_stub.v}
// Design      : mult_gen_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tfgg484-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "mult_gen_v12_0_16,Vivado 2019.2" *)
module mult_gen_0(CLK, A, B, P)
/* synthesis syn_black_box black_box_pad_pin="CLK,A[23:0],B[23:0],P[47:0]" */;
  input CLK;
  input [23:0]A;
  input [23:0]B;
  output [47:0]P;
endmodule
