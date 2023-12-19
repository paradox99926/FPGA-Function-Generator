`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 10:21:58
// Design Name:
// Module Name: UART_Byte_Rx
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

module UART_Byte_Rx(Clk,
                    Rst_n,
                    Baud_Set,
                    Rs232_Rx,
                    Data_Byte,
                    Rx_Done);
    
    input Clk;
    input Rst_n;
    input Baud_Set;
    input Rs232_Rx;
    output reg [7:0]Data_Byte;
    output reg Rx_Done;
    
    reg s0_Rs232_Rx;
    reg s1_Rs232_Rx;
    reg tmp0_Rs232_Rx;
    reg tmp1_Rs232_Rx;
    reg uart_state;
    reg [2:0]START_BIT;
    reg [2:0]STOP_BIT;
    
    wire nedge;
    
    //同步寄存器，消除亚稳
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)begin
            s0_Rs232_Rx <= 1'b0;
            s1_Rs232_Rx <= 1'b0;
        end
        else begin
            s0_Rs232_Rx <= Rs232_Rx;
            s1_Rs232_Rx <= s0_Rs232_Rx;
        end
        //数据寄存
        always @(posedge Clk or negedge Rst_n)
            if (!Rst_n)begin
                tmp0_Rs232_Rx <= 1'b0;
                tmp1_Rs232_Rx <= 1'b0;
            end
            else begin
                tmp0_Rs232_Rx <= s1_Rs232_Rx;
                tmp1_Rs232_Rx <= tmp0_Rs232_Rx;
            end
            assign nedge = (!tmp0_Rs232_Rx) && tmp1_Rs232_Rx;
    
    //设置波特
    reg [15:0] bps_DR;
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_DR <= 16'd3811;
        else begin
            case (Baud_Set)
                0:bps_DR       <= 16'd811;//9600, 104167/ System_clk_period/16-1
                1:bps_DR       <= 16'd404;//19200, 52083/ System_clk_period/16-1
                2:bps_DR       <= 16'd201;//38400, 26041/ System_clk_period/16-1
                3:bps_DR       <= 16'd133;//57600, 17361/ System_clk_period/16-1
                4:bps_DR       <= 16'd65;//115200, 8680/ System_clk_period/16-1
                default:bps_DR <= 16'd811;
            endcase
        end
    
    //分频
    reg [15:0]div_cnt;
    reg bps_clk;
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            div_cnt <= 16'd0;
        else if (uart_state)begin
            if (div_cnt == bps_DR)
                div_cnt <= 16'd0;
            else
                div_cnt <= div_cnt +1'b1;
        end
        else
            div_cnt <= 16'd0;
    
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_clk <= 1'b0;
        else if (div_cnt == 16'd1)
            bps_clk <= 1'b1;
        else
            bps_clk <= 1'b0;
    
    //采样时钟计数
    reg [7:0]bps_cnt;
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_cnt <= 8'd0;
        else if (bps_cnt == 8'd159 || (bps_cnt == 8'd12 && (START_BIT > 2)))
            bps_cnt <= 8'd0;
        else if (bps_clk)
            bps_cnt <= bps_cnt +1'b1;
        else
            bps_cnt <= bps_cnt;
    
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            Rx_Done <= 1'b0;
        else if (bps_cnt == 8'd159)
            Rx_Done <= 1'b1;
        else
            Rx_Done <= 1'b0;
    
    //采样数据接收模块
    reg [2:0]r_data_byte[7:0];//8-*3| Matrix
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)begin
            START_BIT      <= 3'b0;
            r_data_byte[0] <= 3'd0;
            r_data_byte[1] <= 3'd0;
            r_data_byte[2] <= 3'd0;
            r_data_byte[3] <= 3'd0;
            r_data_byte[4] <= 3'd0;
            r_data_byte[5] <= 3'd0;
            r_data_byte[6] <= 3'd0;
            r_data_byte[7] <= 3'd0;
            STOP_BIT = 3'd0;
        end
        else if (bps_clk)begin
            case (bps_cnt)
                0:begin
                    START_BIT = 3'd0;
                    r_data_byte[0] <= 3'd0;
                    r_data_byte[1] <= 3'd0;
                    r_data_byte[2] <= 3'd0;
                    r_data_byte[3] <= 3'd0;
                    r_data_byte[4] <= 3'd0;
                    r_data_byte[5] <= 3'd0;
                    r_data_byte[6] <= 3'd0;
                    r_data_byte[7] <= 3'd0;
                    STOP_BIT = 3'd0;
                end
                6,7,8,9,10,11:START_BIT                <= START_BIT + s1_Rs232_Rx;
                22,23,24,25,26,27:r_data_byte[0]       <= r_data_byte[0] + s1_Rs232_Rx;
                38,39,40,41,42,43:r_data_byte[1]       <= r_data_byte[1] + s1_Rs232_Rx;
                54,55,56,57,58,59:r_data_byte[2]       <= r_data_byte[2] + s1_Rs232_Rx;
                70,71,72,73,74,75:r_data_byte[3]       <= r_data_byte[3] + s1_Rs232_Rx;
                86,87,88,89,90,91:r_data_byte[4]       <= r_data_byte[4] + s1_Rs232_Rx;
                102,103,104,105,106,107:r_data_byte[5] <= r_data_byte[5] + s1_Rs232_Rx;
                118,119,120,121,122,123:r_data_byte[6] <= r_data_byte[6] + s1_Rs232_Rx;
                134,135,136,137,138,139:r_data_byte[7] <= r_data_byte[7] + s1_Rs232_Rx;
                150,151,152,153,154,155:STOP_BIT       <= STOP_BIT + s1_Rs232_Rx;
                default:
                begin
                    START_BIT = START_BIT;
                    r_data_byte[0] <= r_data_byte[0];
                    r_data_byte[1] <= r_data_byte[1];
                    r_data_byte[2] <= r_data_byte[2];
                    r_data_byte[3] <= r_data_byte[3];
                    r_data_byte[4] <= r_data_byte[4];
                    r_data_byte[5] <= r_data_byte[5];
                    r_data_byte[6] <= r_data_byte[6];
                    r_data_byte[7] <= r_data_byte[7];
                    STOP_BIT = STOP_BIT;
                end
            endcase
        end
            
            
            always@(posedge Clk or negedge Rst_n)
                if (!Rst_n)
                    uart_state <= 1'b0;
                else if (nedge)
                    uart_state <= 1'b1;
                else if (Rx_Done || (bps_cnt == 8'd12 && (START_BIT > 2)))
                    uart_state <= 1'b0;
                else
                    uart_state <= uart_state;
            
            
            // 数据state判定
            always @(posedge Clk or negedge Rst_n)
                if (!Rst_n)
                    Data_Byte <= 8'd0;
                else if (bps_cnt == 8'd159)begin
                    Data_Byte[0] <= r_data_byte[0][2];
                    Data_Byte[1] <= r_data_byte[1][2];
                    Data_Byte[2] <= r_data_byte[2][2];
                    Data_Byte[3] <= r_data_byte[3][2];
                    Data_Byte[4] <= r_data_byte[4][2];
                    Data_Byte[5] <= r_data_byte[5][2];
                    Data_Byte[6] <= r_data_byte[6][2];
                    Data_Byte[7] <= r_data_byte[7][2];
                end
                    
                    endmodule
