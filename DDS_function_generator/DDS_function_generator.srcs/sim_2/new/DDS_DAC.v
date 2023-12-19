`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 25.11.2023 16:22:25
// Design Name:
// Module Name: DDS_Module_tb
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////
`define clk_period 8

module DDS_DAC();
    reg Clk;
    reg Rst_n;
    reg [31:0]Fword0;
    reg [31:0]Fword1;
    reg [11:0]Pword0;
    reg [11:0]Pword1;
    reg [11:0]Aword0;
    reg [11:0]Aword1;
    reg [3:0]CH_Sync;
    
    wire [13:0]DA_Data;
    wire [13:0]DB_Data;
    wire [9:0]DA_out;
    wire [9:0]DB_out;
    
    
    //DDS_A
    DDS_Module DDS_A(
    .Clk(Clk),
    .Reset_n(Rst_n),
    .Mode_Sel(CH_Sync[3:2]),
    .Fword(Fword0),
    .Pword(Pword0),
    .Data(DA_Data));
    
    //DDS_B
    DDS_Module DDS_B(
    .Clk(Clk),
    .Reset_n(Rst_n),
    .Mode_Sel(CH_Sync[1:0]),
    .Fword(Fword1),
    .Pword(Pword1),
    .Data(DB_Data)
    );
    
    //DAC适配模块
    DAC_adapter DAC_adapter(
    .DA_Data(DA_Data),
    .Clk(Clk),
    .Rst_n(Rst_n),
    .DB_Data(DB_Data),
    .Aword0(Aword0),
    .Aword1(Aword1),
    .DA_out(DA_out),
    .DB_out(DB_out)
    );
    
    initial Clk                = 1;
    always #(`clk_period/2)Clk = ~Clk;
    
    initial begin
        Rst_n   = 0;
        Fword0  = 65536;
        Fword1  = 65536;
        Pword0  = 0;
        Pword1  = 0;
        Aword0  = 4095;
        Aword1  = 4095;
        CH_Sync = 4'b0100;
        #201;
        Rst_n   = 1;
        CH_Sync = 4'b1010;
        #(`clk_period*100_000);
        Fword0 = 65536*1024;
        Fword1 = 65536*1024;
        Pword0 = 0;
        Pword1 = 0;
        Aword0 = 3120;
        Aword1 = 1024;
        #(`clk_period*100_000);
        CH_Sync = 4'b0111;
        Fword0  = 65536*128;
        Fword1  = 65536*32;
        Pword0  = 2048;
        Pword1  = 1024;
        Aword0  = 4095;
        Aword1  = 4095;
        #(`clk_period*100_000);
        $stop;
    end
    
    
endmodule
