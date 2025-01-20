`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 20:40:52
// Design Name:
// Module Name: DDS_function_generator_top
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


module DDS_function_generator_top(Clk,
                                  Rs232_Rx,
                                  Rst_n,
                                  DA_out,
                                  DB_out,
                                  DA1_Clk);
    
    input    Clk;
    input    Rs232_Rx;
    input    Rst_n;
    output   [9:0]DA_out;
    output   [9:0]DB_out;
    output   wire DA1_Clk;
    // output   wire DA2_CLK;
    
    wire Clk125M;
    wire [7:0]Data_Byte;
    wire Rx_Done;
    wire [31:0]Fword0;
    wire [31:0]Fword1;
    wire [11:0]Pword0;
    wire [11:0]Pword1;
    wire [11:0]Aword0;
    wire [11:0]Aword1;
    wire [15:0]Cus_Point1X;
    wire [15:0]Cus_Point2X;
    wire [15:0]Cus_Point3X;
    wire [15:0]Cus_Point4X;
    wire [15:0]Cus_Point5X;
    wire [15:0]Cus_Point6X;
    wire [15:0]Cus_Point7X;
    wire [15:0]Cus_Point8X;
    wire [15:0]Cus_Point1Y;
    wire [15:0]Cus_Point2Y;
    wire [15:0]Cus_Point3Y;
    wire [15:0]Cus_Point4Y;
    wire [15:0]Cus_Point5Y;
    wire [15:0]Cus_Point6Y;
    wire [15:0]Cus_Point7Y;
    wire [15:0]Cus_Point8Y;
    
    
    wire [5:0]CH_Sync;
    wire [13:0]DA_Data;
    wire [13:0]DB_Data;
    
    
    
    //锁相环，产生125M时钟，与DAC适配
    PLL PLL(.clk_in1(Clk),
    .resetn(Rst_n),
    .clk_out1(Clk125M)
    );
    
    //接收模块
    UART_Byte_Rx UART_Byte_Rx(.Clk(Clk125M),
    .Rst_n(Rst_n),
    .Baud_Set(3'd0),//9600
    .Rs232_Rx(Rs232_Rx),
    .Data_Byte(Data_Byte),
    .Rx_Done(Rx_Done)
    );
    
    //解析模块
    CMD CMD(.Clk(Clk125M),
    .Rst_n(Rst_n),
    .Rx_byte(Data_Byte),
    .Rx_int(Rx_Done),
    .Fword0(Fword0),
    .Fword1(Fword1),
    .Pword0(Pword0),
    .Pword1(Pword1),
    .Aword0(Aword0),
    .Aword1(Aword1),
    .Cus_Point1X(Cus_Point1X),
    .Cus_Point2X(Cus_Point2X),
    .Cus_Point3X(Cus_Point3X),
    .Cus_Point4X(Cus_Point4X),
    .Cus_Point5X(Cus_Point5X),
    .Cus_Point6X(Cus_Point6X),
    .Cus_Point7X(Cus_Point7X),
    .Cus_Point8X(Cus_Point8X),
    .Cus_Point1Y(Cus_Point1Y),
    .Cus_Point2Y(Cus_Point2Y),
    .Cus_Point3Y(Cus_Point3Y),
    .Cus_Point4Y(Cus_Point4Y),
    .Cus_Point5Y(Cus_Point5Y),
    .Cus_Point6Y(Cus_Point6Y),
    .Cus_Point7Y(Cus_Point7Y),
    .Cus_Point8Y(Cus_Point8Y),
    .CH_Sync(CH_Sync)
    );
    
    //DDS_A
    DDS_Module DDS_A(.Clk(Clk125M),
    .Reset_n(Rst_n),
    .Mode_Sel(CH_Sync[5:3]),
    .Fword(Fword0),
    .Pword(Pword0),
    .Cus_Point1X(Cus_Point1X),
    .Cus_Point2X(Cus_Point2X),
    .Cus_Point3X(Cus_Point3X),
    .Cus_Point4X(Cus_Point4X),
    .Cus_Point5X(Cus_Point5X),
    .Cus_Point6X(Cus_Point6X),
    .Cus_Point7X(Cus_Point7X),
    .Cus_Point8X(Cus_Point8X),
    .Cus_Point1Y(Cus_Point1Y),
    .Cus_Point2Y(Cus_Point2Y),
    .Cus_Point3Y(Cus_Point3Y),
    .Cus_Point4Y(Cus_Point4Y),
    .Cus_Point5Y(Cus_Point5Y),
    .Cus_Point6Y(Cus_Point6Y),
    .Cus_Point7Y(Cus_Point7Y),
    .Cus_Point8Y(Cus_Point8Y),
    .Data(DA_Data));
    
    
    //DDS_B
    DDS_Module DDS_B(.Clk(Clk125M),
    .Reset_n(Rst_n),
    .Mode_Sel(CH_Sync[2:0]),
    .Fword(Fword1),
    .Pword(Pword1),
    .Cus_Point1X(Cus_Point1X),
    .Cus_Point2X(Cus_Point2X),
    .Cus_Point3X(Cus_Point3X),
    .Cus_Point4X(Cus_Point4X),
    .Cus_Point5X(Cus_Point5X),
    .Cus_Point6X(Cus_Point6X),
    .Cus_Point7X(Cus_Point7X),
    .Cus_Point8X(Cus_Point8X),
    .Cus_Point1Y(Cus_Point1Y),
    .Cus_Point2Y(Cus_Point2Y),
    .Cus_Point3Y(Cus_Point3Y),
    .Cus_Point4Y(Cus_Point4Y),
    .Cus_Point5Y(Cus_Point5Y),
    .Cus_Point6Y(Cus_Point6Y),
    .Cus_Point7Y(Cus_Point7Y),
    .Cus_Point8Y(Cus_Point8Y),
    .Data(DB_Data)
    );
    
    //DAC适配模块
    DAC_adapter DAC_adapter(
    .DA_Data(DA_Data),
    .Clk(Clk125M),
    .Rst_n(Rst_n),
    .DB_Data(DB_Data),
    .Aword0(Aword0),
    .Aword1(Aword1),
    .DA_out(DA_out),
    .DB_out(DB_out)
    );
    
    assign DA1_Clk    = Clk125M;
    // assign DA2_CLK = DA1_Clk;
    
endmodule
