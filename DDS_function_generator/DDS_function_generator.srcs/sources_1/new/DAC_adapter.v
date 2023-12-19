`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 28.11.2023 17:19:50
// Design Name:
// Module Name: DAC_adapter
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


module DAC_adapter(DA_Data,
                   Clk,
                   Rst_n,
                   DB_Data,
                   Aword0,
                   Aword1,
                   DA_out,
                   DB_out);
    
    input  [13:0]DA_Data;
    input  Clk;
    input  Rst_n;
    input  [13:0]DB_Data;
    input  [11:0]Aword0;
    input  [11:0]Aword1;
    output reg[9:0] DA_out;
    output reg[9:0] DB_out;
    //DDS_A
    wire [23:0]mulA_A;
    wire [23:0]mulB_A;
    wire [47:0]mulA_out;
    //DDS_B
    wire [23:0]mulA_B;
    wire [23:0]mulB_B;
    wire [47:0]mulB_out;
    
    assign mulA_A = {12'd0,Aword0[11:0]};
    assign mulA_B = {12'd0,Aword1[11:0]};
    assign mulB_A = {10'd0,DA_Data[13:0]};
    assign mulB_B = {10'd0,DB_Data[13:0]};
    
    // wire [15:0]divisorA;
    // wire [15:0]dividendA;
    // wire divisor_validA;
    // wire dividend_validA;
    // wire [31:0]div_outA;//low16位是余数
    
    // wire [15:0]divisorB;
    // wire [15:0]dividendB;
    // wire divisor_validB;
    // wire dividend_validB;
    // wire [31:0]div_outB;//low16位是余数
    
    // wire [9:0]Aword0_10;
    // wire [9:0]Aword1_10;
    
    // assign Aword0_10 = Aword0[11:2];
    // assign Aword1_10 = Aword1[11:2];
    
    reg [23:0]mul_right_A;
    reg [23:0]mul_right_B;
    
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)begin
            DA_out <= 0;
        end
        else
        begin
            mul_right_A <= (mulA_out>>12);
            DA_out      <= mul_right_A[13:4];
        end
    
    always @(posedge Clk or negedge Rst_n)
        if (!Rst_n)begin
            DB_out <= 0;
        end
        else
        begin
            mul_right_B <= (mulB_out>>12);
            DB_out      <= mul_right_B[13:4];
        end
        // reg validA;
        // reg validB;
        // assign divisor_validA  = validA;
        // assign dividend_validA = validA;
        // assign divisor_validA  = validA;
        // assign dividend_validA = validA;
        // assign divisorA        = {6'd0,Aword0_10};
        // assign dividendA       = {6'd0,DA_Data[13:4]};
        // always @(posedge Clk or negedge Rst_n)
        //     if (!Rst_n)begin
        //         DA_out <= 10'd0;
        //     end
        //     else
        //     begin
        //         if (Aword0[7:0] == 0)begin
        //             validA <= 0;
        //             DA_out <= DA_Data[13:4];
        //         end
        //         else begin
        //             validA <= 1;
        //             DA_out <= div_outA[25:16];
    
    //         end
    //     end
    
    
    
    
    // assign divisor_validB  = validB;
    // assign dividend_validB = validB;
    // assign divisor_validB  = validB;
    // assign dividend_validB = validB;
    // assign divisorB        = {6'd0,Aword1_10};
    // assign dividendB       = {6'd0,DB_Data[13:4]};
    // always @(posedge Clk or negedge Rst_n)
    //     if (!Rst_n)begin
    //         DB_out <= 10'd0;
    //     end
    //     else
    //     begin
    //         if (Aword1[7:0] == 0)begin
    //             validB <= 0;
    //             DB_out <= DB_Data[13:4];
    //         end
    //         else begin
    //             validB <= 1;
    //             DB_out <= div_outB[25:16];
    
    //         end
    //     end
    
    mult_gen_0 multiplierA(
    .CLK(Clk),
    .A(mulA_A),
    .B(mulB_A),
    .P(mulA_out)
    );
    
    
    mult_gen_0 multiplierB(
    .CLK(Clk),
    .A(mulA_B),
    .B(mulB_B),
    .P(mulB_out)
    );
    // divider dividerA(
    // .aclk(Clk),
    // .s_axis_divisor_tdata(divisorA),
    // .s_axis_dividend_tdata(dividendA),
    // .s_axis_divisor_tvalid(divisor_validA),
    // .s_axis_dividend_tvalid(dividend_validA),
    // .m_axis_dout_tdata(div_outA),
    // .m_axis_dout_tuser(),
    // .m_axis_dout_tvalid()
    // );
    
    // divider dividerB(
    // .aclk(Clk),
    // .s_axis_divisor_tdata(divisorB),
    // .s_axis_dividend_tdata(dividendB),
    // .s_axis_divisor_tvalid(divisor_validB),
    // .s_axis_dividend_tvalid(dividend_validB),
    // .m_axis_dout_tdata(div_outB),
    // .m_axis_dout_tuser(),
    // .m_axis_dout_tvalid()
    // );
    
endmodule
