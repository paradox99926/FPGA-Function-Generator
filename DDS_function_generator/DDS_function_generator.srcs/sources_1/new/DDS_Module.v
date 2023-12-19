`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 17:00:00
// Design Name:
// Module Name: DDS_Module
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

//Fword  = (2**32)*Fout/Fclk;
//PwordA = degree/360*4096;
module DDS_Module(Clk,
                  Reset_n,
                  Mode_Sel,
                  Fword,
                  Pword,
                  Data);
    
    input Clk;
    input Reset_n;
    input [1:0]Mode_Sel;
    input [31:0]Fword;//频率控制
    input [11:0] Pword;//相位控制
    output reg[13:0]Data;//14位DAC模块
    
    wire [13:0]Data_sin;
    wire [13:0]Data_square;
    wire [13:0]Data_triangular;
    
    
    always @(*)
        case (Mode_Sel)
            0: Data       <= Data_sin;
            1: Data       <= Data_square;
            2: Data       <= Data_triangular;
            3: Data       <= 16352;//输出0电平
            default: Data <= 0;
        endcase
    
    
    //频率控制字同步寄存器
    reg [31:0]Fword_r;
    always @(posedge Clk or negedge Reset_n)
        if (!Reset_n)
            Fword_r <= 0;
        else
            Fword_r <= Fword;
    
    //相位控制字同步寄存器
    reg [31:0]Pword_r;
    always @(posedge Clk or negedge Reset_n)
        if (!Reset_n)
            Pword_r <= 0;
        else
            Pword_r <= Pword;
    
    //相位累加
    reg [31:0] Freq_ACC;
    always @(posedge Clk or negedge Reset_n)
        if (!Reset_n)
            Freq_ACC <= 32'd0;
        else
            Freq_ACC <= Fword_r + Freq_ACC;
    
    
    // //相位累加器与相位控制字的结果输出
    // reg [31:0]Freq_ACC_out;
    // always @(posedge Clk or negedge Reset_n)
    //     if (!Reset_n)
    //         Freq_ACC_out <= 0;
    //     else
    //         Freq_ACC_out <= Freq_ACC;
    
    // 波形数据表address
    wire [11:0]Rom_Addr;
    assign Rom_Addr = Freq_ACC[31:20] + Pword_r;
    
    rom_sin rom_sin(
    .clka(Clk),
    .addra(Rom_Addr),
    .douta(Data_sin)
    );
    
    rom_triangular rom_triangular(
    .clka(Clk),
    .addra(Rom_Addr),
    .douta(Data_triangular)
    );
    
    rom_square rom_square(
    .clka(Clk),
    .addra(Rom_Addr),
    .douta(Data_square)
    );
    
    
endmodule
