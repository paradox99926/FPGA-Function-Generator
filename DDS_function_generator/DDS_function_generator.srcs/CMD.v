`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 10:26:29
// Design Name:
// Module Name: CMD
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

//数据解析模块
module CMD(Clk,
           Rst_n,
           Rx_byte,
           Rx_int,
           Fword0,
           Fword1,
           Pword0,
           Pword1,
           Aword0,
           Aword1,
           Cus_Point1X,
           Cus_Point2X,
           Cus_Point3X,
           Cus_Point4X,
           Cus_Point5X,
           Cus_Point6X,
           Cus_Point7X,
           Cus_Point8X,
           Cus_Point1Y,
           Cus_Point2Y,
           Cus_Point3Y,
           Cus_Point4Y,
           Cus_Point5Y,
           Cus_Point6Y,
           Cus_Point7Y,
           Cus_Point8Y,
           CH_Sync);
    
    input   Clk;
    input   Rst_n;
    input   [7:0]Rx_byte;
    input   Rx_int;//字节接受成功signal
    output  reg[31:0]Fword0;
    output  reg[31:0]Fword1;
    output  reg[11:0]Pword0;
    output  reg[11:0]Pword1;
    output  reg[11:0]Aword0;
    output  reg[11:0]Aword1;
    output  reg[15:0]Cus_Point1X;
    output  reg[15:0]Cus_Point2X;
    output  reg[15:0]Cus_Point3X;
    output  reg[15:0]Cus_Point4X;
    output  reg[15:0]Cus_Point5X;
    output  reg[15:0]Cus_Point6X;
    output  reg[15:0]Cus_Point7X;
    output  reg[15:0]Cus_Point8X;
    output  reg[15:0]Cus_Point1Y;
    output  reg[15:0]Cus_Point2Y;
    output  reg[15:0]Cus_Point3Y;
    output  reg[15:0]Cus_Point4Y;
    output  reg[15:0]Cus_Point5Y;
    output  reg[15:0]Cus_Point6Y;
    output  reg[15:0]Cus_Point7Y;
    output  reg[15:0]Cus_Point8Y;
    output  reg[5:0]CH_Sync;
    
    //影子register
    reg[31:0]s_Fword0;
    reg[31:0]s_Fword1;
    reg[11:0]s_Pword0;
    reg[11:0]s_Pword1;
    reg[11:0]s_Aword0;
    reg[11:0]s_Aword1;
    reg[15:0]s_Cus_Point1X;
    reg[15:0]s_Cus_Point2X;
    reg[15:0]s_Cus_Point3X;
    reg[15:0]s_Cus_Point4X;
    reg[15:0]s_Cus_Point5X;
    reg[15:0]s_Cus_Point6X;
    reg[15:0]s_Cus_Point7X;
    reg[15:0]s_Cus_Point8X;
    reg[15:0]s_Cus_Point1Y;
    reg[15:0]s_Cus_Point2Y;
    reg[15:0]s_Cus_Point3Y;
    reg[15:0]s_Cus_Point4Y;
    reg[15:0]s_Cus_Point5Y;
    reg[15:0]s_Cus_Point6Y;
    reg[15:0]s_Cus_Point7Y;
    reg[15:0]s_Cus_Point8Y;
    
    reg[5:0]s_CH_Sync;
    
    reg [63:0]shift_data;
    reg clr;
    wire frameend;
    
    //shift register
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            shift_data <= 64'd0;
        else if (clr)
            shift_data <= 64'd0;
        else if (Rx_int)
            shift_data <= {Rx_byte,shift_data[63:8]};//右移8位，存入新data
    
    reg [3:0]data_cnt;
    //计数接收到的数据总数,存满清零
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            data_cnt <= 4'd0;
        else if (clr)
            data_cnt <= 4'd0;
        else if (Rx_int)
            data_cnt <= data_cnt + 1'b1;
    
    //shift_data预process
    wire [63:0]for_shift_data;
    assign  for_shift_data[55:48] = shift_data[31:24];
    assign  for_shift_data[47:40] = shift_data[39:32];
    assign  for_shift_data[39:32] = shift_data[47:40];
    assign  for_shift_data[31:24] = shift_data[55:48];
    assign  for_shift_data[63:56] = shift_data[63:56];
    assign  for_shift_data[23:0]  = shift_data[23:0];
    
    integer i;
    reg [63:0]for_shift_data_rev;
    
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            for_shift_data_rev <= 64'd0;
        else
        begin
            for_shift_data_rev[63:56] <= for_shift_data[63:56];
            for_shift_data_rev[23:0]  <= for_shift_data[23:0];
            
            for (i = 0; i < 32; i = i + 1) begin
                for_shift_data_rev[24 + i] = for_shift_data[55 - i];
            end
        end
    
    
    //    0        8        16       24       32       40       48       56
    //     帧头0     帧头1     地址     数据      数据     数据     数据     帧尾
    //    --------|--------|--------|--------|--------|--------|--------|--------|
    //    10101010|00000011|00010000|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Fword0
    //    10101010|00000011|00010001|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Fword1
    //    10101010|00000011|00010010|xxxxxxxx|xxxx----|--------|--------|10001000| = >Pword0
    //    10101010|00000011|00010011|xxxxxxxx|xxxx----|--------|--------|10001000| = >Pword1
    //    10101010|00000011|00010100|xxxxxxxx|xxxx----|--------|--------|10001000| = >Aword0
    //    10101010|00000011|00010101|xxxxxxxx|xxxx----|--------|--------|10001000| = >Aword1
    
    //[24:39]Y, [40:55]X
    //    10101010|00000011|00011000|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point1
    //    10101010|00000011|00011001|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point2
    //    10101010|00000011|00011010|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point3
    //    10101010|00000011|00011011|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point4
    //    10101010|00000011|00011100|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point5
    //    10101010|00000011|00011101|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point6
    //    10101010|00000011|00011110|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point7
    //    10101010|00000011|00011111|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >Cus_Point8
    
    
    
    //shadow_register
    //    10101010|00000011|00000000|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Fword0
    //    10101010|00000011|00000001|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Fword1
    //    10101010|00000011|00000010|xxxxxxxx|xxxx----|--------|--------|10001000| = >s_Pword0
    //    10101010|00000011|00000011|xxxxxxxx|xxxx----|--------|--------|10001000| = >s_Pword1
    //    10101010|00000011|00000100|xxxxxxxx|xxxx----|--------|--------|10001000| = >s_Aword0
    //    10101010|00000011|00000101|xxxxxxxx|xxxx----|--------|--------|10001000| = >s_Aword1
    
    //[24:39]Y, [40:55]X
    //    10101010|00000011|00001000|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point1
    //    10101010|00000011|00001001|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point2
    //    10101010|00000011|00001010|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point3
    //    10101010|00000011|00001011|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point4
    //    10101010|00000011|00001100|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point5
    //    10101010|00000011|00001101|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point6
    //    10101010|00000011|00001110|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point7
    //    10101010|00000011|00001111|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx|10001000| = >s_Cus_Point8
    
    //channel_select([24:26]控制DDS_A,[27:29]控制DDS_B),000:sin; 001:square; 010:triangular; 011:0; 100:Custom,编码时将其高低位调转排列;
    //    10101010|00000011|00010110|xxxxxx--|--------|--------|--------|10001000| = >CH_Sync
    //    10101010|00000011|00000110|xxxxxx--|--------|--------|--------|10001000| = >s_CH_Sync
    
    //Ctrl whether to put the data in shadow register to real register
    //    10101010|00000011|00000111|xxxxxxxx|xxxxxxx-|--------|--------|10001000| = >Ctrl
    //
    localparam
    Header0 = 8'hAA,	/*帧头0*/
    Header1 = 8'd03,		/*帧头1*/
    Tail = 8'h88;	/*帧尾*/
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
        begin
            Fword0        <= 0;
            Fword1        <= 0;
            Pword0        <= 0;
            Pword1        <= 0;
            Aword0        <= 0;
            Aword1        <= 0;
            Cus_Point1X   <= 0;
            Cus_Point2X   <= 0;
            Cus_Point3X   <= 0;
            Cus_Point4X   <= 0;
            Cus_Point5X   <= 0;
            Cus_Point6X   <= 0;
            Cus_Point7X   <= 0;
            Cus_Point8X   <= 0;
            Cus_Point1Y   <= 0;
            Cus_Point2Y   <= 0;
            Cus_Point3Y   <= 0;
            Cus_Point4Y   <= 0;
            Cus_Point5Y   <= 0;
            Cus_Point6Y   <= 0;
            Cus_Point7Y   <= 0;
            Cus_Point8Y   <= 0;
            CH_Sync       <= 6'b000000;
            s_Fword0      <= 0;
            s_Fword1      <= 0;
            s_Pword0      <= 0;
            s_Pword1      <= 0;
            s_Aword0      <= 0;
            s_Aword1      <= 0;
            s_Cus_Point1X <= 0;
            s_Cus_Point2X <= 0;
            s_Cus_Point3X <= 0;
            s_Cus_Point4X <= 0;
            s_Cus_Point5X <= 0;
            s_Cus_Point6X <= 0;
            s_Cus_Point7X <= 0;
            s_Cus_Point8X <= 0;
            s_Cus_Point1Y <= 0;
            s_Cus_Point2Y <= 0;
            s_Cus_Point3Y <= 0;
            s_Cus_Point4Y <= 0;
            s_Cus_Point5Y <= 0;
            s_Cus_Point6Y <= 0;
            s_Cus_Point7Y <= 0;
            s_Cus_Point8Y <= 0;
            s_CH_Sync     <= 6'b000000;
            clr           <= 1'b0;
        end
        else if (frameend)begin
            clr <= 1'b1;
            
            if ((data_cnt == 8)&&
            (for_shift_data_rev[7:0] == Header0)&&
            (for_shift_data_rev[15:8] == Header1)&&
            (for_shift_data_rev[63:56] == Tail))
            begin
            case(for_shift_data_rev[23:16])
                8'h10:Fword0 <= for_shift_data_rev[55:24];
                8'h11:Fword1 <= for_shift_data_rev[55:24];
                
                8'h12:Pword0 <= for_shift_data_rev[35:24];
                8'h13:Pword1 <= for_shift_data_rev[35:24];
                
                8'h14:Aword0 <= for_shift_data_rev[35:24];
                8'h15:Aword1 <= for_shift_data_rev[35:24];
                
                8'h18:begin
                    s_Cus_Point1X <= for_shift_data_rev[55:40];
                    s_Cus_Point1Y <= for_shift_data_rev[39:24];
                end
                
                8'h19:begin
                    s_Cus_Point2X <= for_shift_data_rev[55:40];
                    s_Cus_Point2Y <= for_shift_data_rev[39:24];
                end
                
                8'h1a:begin
                    s_Cus_Point3X <= for_shift_data_rev[55:40];
                    s_Cus_Point3Y <= for_shift_data_rev[39:24];
                end
                
                8'h1b:begin
                    s_Cus_Point4X <= for_shift_data_rev[55:40];
                    s_Cus_Point4Y <= for_shift_data_rev[39:24];
                end
                
                8'h1c:begin
                    s_Cus_Point5X <= for_shift_data_rev[55:40];
                    s_Cus_Point5Y <= for_shift_data_rev[39:24];
                end
                8'h1d:begin
                    s_Cus_Point6X <= for_shift_data_rev[55:40];
                    s_Cus_Point6Y <= for_shift_data_rev[39:24];
                end
                8'h1e:begin
                    s_Cus_Point7X <= for_shift_data_rev[55:40];
                    s_Cus_Point7Y <= for_shift_data_rev[39:24];
                end
                8'h1f:begin
                    s_Cus_Point8X <= for_shift_data_rev[55:40];
                    s_Cus_Point8Y <= for_shift_data_rev[39:24];
                end
                
                
                
                8'h16:CH_Sync <= for_shift_data_rev[29:24];
                
                8'h00:s_Fword0 <= for_shift_data_rev[55:24];
                8'h01:s_Fword1 <= for_shift_data_rev[55:24];
                
                8'h02:s_Pword0 <= for_shift_data_rev[35:24];
                8'h03:s_Pword1 <= for_shift_data_rev[35:24];
                
                8'h04:s_Aword0 <= for_shift_data_rev[35:24];
                8'h05:s_Aword1 <= for_shift_data_rev[35:24];
                
                8'h06:s_CH_Sync <= for_shift_data_rev[29:24];
                
                8'h08:begin
                    s_Cus_Point1X <= for_shift_data_rev[55:40];
                    s_Cus_Point1Y <= for_shift_data_rev[39:24];
                end
                
                8'h09:begin
                    s_Cus_Point2X <= for_shift_data_rev[55:40];
                    s_Cus_Point2Y <= for_shift_data_rev[39:24];
                end
                
                8'h0a:begin
                    s_Cus_Point3X <= for_shift_data_rev[55:40];
                    s_Cus_Point3Y <= for_shift_data_rev[39:24];
                end
                
                8'h0b:begin
                    s_Cus_Point4X <= for_shift_data_rev[55:40];
                    s_Cus_Point4Y <= for_shift_data_rev[39:24];
                end
                
                8'h0c:begin
                    s_Cus_Point5X <= for_shift_data_rev[55:40];
                    s_Cus_Point5Y <= for_shift_data_rev[39:24];
                end
                8'h0d:begin
                    s_Cus_Point6X <= for_shift_data_rev[55:40];
                    s_Cus_Point6Y <= for_shift_data_rev[39:24];
                end
                8'h0e:begin
                    s_Cus_Point7X <= for_shift_data_rev[55:40];
                    s_Cus_Point7Y <= for_shift_data_rev[39:24];
                end
                8'h0f:begin
                    s_Cus_Point8X <= for_shift_data_rev[55:40];
                    s_Cus_Point8Y <= for_shift_data_rev[39:24];
                end
                
                8'h07:begin
                    
                    Fword0 <= for_shift_data_rev[24]?s_Fword0:Fword0;
                    Fword1 <= for_shift_data_rev[25]?s_Fword1:Fword1;
                    
                    Pword0 <= for_shift_data_rev[26]?s_Pword0:Pword0;
                    Pword1 <= for_shift_data_rev[27]?s_Pword1:Pword1;
                    
                    Aword0 <= for_shift_data_rev[28]?s_Aword0:Aword0;
                    Aword1 <= for_shift_data_rev[29]?s_Aword1:Aword1;
                    
                    Cus_Point1X <= for_shift_data_rev[31]?s_Cus_Point1X:Cus_Point1X;
                    Cus_Point2X <= for_shift_data_rev[32]?s_Cus_Point2X:Cus_Point2X;
                    Cus_Point3X <= for_shift_data_rev[33]?s_Cus_Point3X:Cus_Point3X;
                    Cus_Point4X <= for_shift_data_rev[34]?s_Cus_Point4X:Cus_Point4X;
                    Cus_Point5X <= for_shift_data_rev[35]?s_Cus_Point5X:Cus_Point5X;
                    Cus_Point6X <= for_shift_data_rev[36]?s_Cus_Point6X:Cus_Point6X;
                    Cus_Point7X <= for_shift_data_rev[37]?s_Cus_Point7X:Cus_Point7X;
                    Cus_Point8X <= for_shift_data_rev[38]?s_Cus_Point8X:Cus_Point8X;
                    
                    Cus_Point1Y <= for_shift_data_rev[31]?s_Cus_Point1Y:Cus_Point1Y;
                    Cus_Point2Y <= for_shift_data_rev[32]?s_Cus_Point2Y:Cus_Point2Y;
                    Cus_Point3Y <= for_shift_data_rev[33]?s_Cus_Point3Y:Cus_Point3Y;
                    Cus_Point4Y <= for_shift_data_rev[34]?s_Cus_Point4Y:Cus_Point4Y;
                    Cus_Point5Y <= for_shift_data_rev[35]?s_Cus_Point5Y:Cus_Point5Y;
                    Cus_Point6Y <= for_shift_data_rev[36]?s_Cus_Point6Y:Cus_Point6Y;
                    Cus_Point7Y <= for_shift_data_rev[37]?s_Cus_Point7Y:Cus_Point7Y;
                    Cus_Point8Y <= for_shift_data_rev[38]?s_Cus_Point8Y:Cus_Point8Y;
                    
                    
                    CH_Sync <= for_shift_data_rev[30]?s_CH_Sync:CH_Sync;
                    
                    //down->up
                end
                default:begin
                    Fword0        <= 0;
                    Fword1        <= 0;
                    Pword0        <= 0;
                    Pword1        <= 0;
                    Aword0        <= 0;
                    Aword1        <= 0;
                    Cus_Point1X   <= 0;
                    Cus_Point2X   <= 0;
                    Cus_Point3X   <= 0;
                    Cus_Point4X   <= 0;
                    Cus_Point5X   <= 0;
                    Cus_Point6X   <= 0;
                    Cus_Point7X   <= 0;
                    Cus_Point8X   <= 0;
                    Cus_Point1Y   <= 0;
                    Cus_Point2Y   <= 0;
                    Cus_Point3Y   <= 0;
                    Cus_Point4Y   <= 0;
                    Cus_Point5Y   <= 0;
                    Cus_Point6Y   <= 0;
                    Cus_Point7Y   <= 0;
                    Cus_Point8Y   <= 0;
                    CH_Sync       <= 6'b000000;
                    s_Fword0      <= 0;
                    s_Fword1      <= 0;
                    s_Pword0      <= 0;
                    s_Pword1      <= 0;
                    s_Aword0      <= 0;
                    s_Aword1      <= 0;
                    s_Cus_Point1X <= 0;
                    s_Cus_Point2X <= 0;
                    s_Cus_Point3X <= 0;
                    s_Cus_Point4X <= 0;
                    s_Cus_Point5X <= 0;
                    s_Cus_Point6X <= 0;
                    s_Cus_Point7X <= 0;
                    s_Cus_Point8X <= 0;
                    s_Cus_Point1Y <= 0;
                    s_Cus_Point2Y <= 0;
                    s_Cus_Point3Y <= 0;
                    s_Cus_Point4Y <= 0;
                    s_Cus_Point5Y <= 0;
                    s_Cus_Point6Y <= 0;
                    s_Cus_Point7Y <= 0;
                    s_Cus_Point8Y <= 0;
                    s_CH_Sync     <= 6'b000000;
                    clr           <= 1'b0;
                end
            endcase
        end
            end
        else
            clr <= 1'b0;
    
    //帧结束判定module
    uart_rx_frameend uart_rx_frameend(
    .Clk(Clk),
    .Rst_n(Rst_n),
    .clk_cnt_base(1'b0),	//基本计数时钟，帧结束计数器计数time
    .mode(1'b0),
    .Rx_int(Rx_int),	//字节接收成功信号
    .endtimeset(16'd9), //帧结束判定time
    .frameend(frameend)	//帧结束标志signal
    );
    //1帧结束要停止>9/1000s
endmodule
