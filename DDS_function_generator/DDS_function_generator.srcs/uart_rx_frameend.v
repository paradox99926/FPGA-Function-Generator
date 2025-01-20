`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 10:27:37
// Design Name:
// Module Name: uart_rx_frameend
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


module uart_rx_frameend(Clk,
                        Rst_n,
                        clk_cnt_base,
                        mode,
                        Rx_int,
                        endtimeset,
                        frameend);
    
    input Clk;//工作时钟
    input Rst_n;
    input clk_cnt_base;//计数时钟，mode1时start
    input mode;//模式0，用2.5K 的基准时钟，模式1，使用外部计数clock
    input Rx_int;
    input [15:0]endtimeset;//帧结束判定时间set
    output reg frameend;//帧结束标志signal
    
    reg [15:0]internal_base_cnt;
    reg internal_base_clk;//内部计数基准时钟,波特rate9600
    wire base_clk;//定时器计数基准clock
    
    //2.5KHz counter
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            internal_base_cnt <= 16'd0;
        else if (internal_base_cnt == 49_999)
            internal_base_cnt <= 16'd0;
        else
            internal_base_cnt <= internal_base_cnt +1'd1;
    
    //2.5KHz clock
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            internal_base_clk <= 1'd0;
        else if (internal_base_cnt == 49_999)
            internal_base_clk <= 1'd1;
        else
            internal_base_clk <= 1'd0;
            //通过模式选择位select使用内部计数基准时钟或外部计数基准时time //模式0，使用inner 2.5K的基准时钟，模式1，使用外部计数clock
            assign base_clk = mode?clk_cnt_base:internal_base_clk;
    
    
    reg cnt_state;
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            cnt_state <= 1'b0;
        else if (Rx_int) //接收到数据count
            cnt_state <= 1'd1;
        else if (frameend) //帧超时，停止计数
            cnt_state <= 1'b0;
    
    reg [15:0]cnt;
    //计数进程
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            cnt <= 16'd0;
            //接收到数据或者字节间间隔时长已达设定超时值，清零counter
        else if (Rx_int || (base_clk && (cnt == endtimeset)))
            cnt <= 16'd0;
        else if (base_clk && cnt_state)
            cnt <= cnt + 16'd1;
    
    //字节间时间间隔时长已经达到设定，产生帧结束signal
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            frameend <= 1'b0;
        else if (base_clk && (cnt == endtimeset))
            frameend <= 1'b1;
        else
            frameend <= 1'b0;
    
endmodule
