`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 19.02.2024 16:54:21
// Design Name:
// Module Name: ram_custom
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


module ram_custom(Reset_n,
                  clka,
                  addr_Read,
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
                  douta);
    
    input Reset_n;
    input clka;
    input wire [11:0]addr_Read;
    input [15:0]Cus_Point1X;
    input [15:0]Cus_Point2X;
    input [15:0]Cus_Point3X;
    input [15:0]Cus_Point4X;
    input [15:0]Cus_Point5X;
    input [15:0]Cus_Point6X;
    input [15:0]Cus_Point7X;
    input [15:0]Cus_Point8X;
    input [15:0]Cus_Point1Y;
    input [15:0]Cus_Point2Y;
    input [15:0]Cus_Point3Y;
    input [15:0]Cus_Point4Y;
    input [15:0]Cus_Point5Y;
    input [15:0]Cus_Point6Y;
    input [15:0]Cus_Point7Y;
    input [15:0]Cus_Point8Y;
    
    output wire[13:0]douta;
    
    
    reg [11:0]addrW;
    reg [13:0]dina;
    wire [11:0]addr_Write;
    wire [13:0]data_Wirte;
    
    wire signed [31:0]dout_tdata1;
    wire signed [31:0]dout_tdata2;
    wire signed [31:0]dout_tdata3;
    wire signed [31:0]dout_tdata4;
    wire signed [31:0]dout_tdata5;
    wire signed [31:0]dout_tdata6;
    wire signed [31:0]dout_tdata7;
    
    wire dout_tvalid1;
    wire dout_tvalid2;
    wire dout_tvalid3;
    wire dout_tvalid4;
    wire dout_tvalid5;
    wire dout_tvalid6;
    wire dout_tvalid7;
    
    reg signed [13:0]k1;
    reg signed [13:0]k2;
    reg signed [13:0]k3;
    reg signed [13:0]k4;
    reg signed [13:0]k5;
    reg signed [13:0]k6;
    reg signed [13:0]k7;
    
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            addrW <= 12'd0;
        else
            addrW <= addrW + 1'b1;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k1 <= 0;
        else if (dout_tvalid1)
            k1 <= dout_tdata1[24:11];
        else
            k1 <= k1;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k2 <= 0;
        else if (dout_tvalid2)
            k2 <= dout_tdata2[24:11];
        else
            k2 <= k2;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k3 <= 0;
        else if (dout_tvalid3)
            k3 <= dout_tdata3[24:11];
        else
            k3 <= k3;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k4 <= 0;
        else if (dout_tvalid4)
            k4 <= dout_tdata4[24:11];
        else
            k4 <= k4;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k5 <= 0;
        else if (dout_tvalid5)
            k5 <= dout_tdata5[24:11];
        else
            k5 <= k5;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k6 <= 0;
        else if (dout_tvalid6)
            k6 <= dout_tdata6[24:11];
        else
            k6 <= k6;
    
    always @(posedge clka or negedge Reset_n)
        if (!Reset_n)
            k7 <= 0;
        else if (dout_tvalid7)
            k7 <= dout_tdata7[24:11];
        else
            k7 <= k7;
    
    
    always @(posedge clka or negedge Reset_n)
    begin
        if (!Reset_n)
            dina <= 0;
        
        else if (addrW<Cus_Point2X[13:0]+1'b1)
        dina <= $signed(k1)*({1'b0, addrW}-{1'b0,Cus_Point1X[13:0]})+{1'b0,Cus_Point1Y[13:0]};
        
        else if ((addrW<Cus_Point3X[13:0]+1'b1)&& (addrW>Cus_Point2X[13:0]))
        dina <= $signed(k2)*({1'b0, addrW}-{1'b0,Cus_Point2X[13:0]})+{1'b0,Cus_Point2Y[13:0]};
        
        else if ((addrW<Cus_Point4X[13:0]+1'b1)&& (addrW>Cus_Point3X[13:0]))
        dina <= $signed(k3)*({1'b0, addrW}-{1'b0,Cus_Point3X[13:0]})+{1'b0,Cus_Point3Y[13:0]};
        
        else if ((addrW<Cus_Point5X[13:0]+1'b1)&& (addrW>Cus_Point4X[13:0]))
        dina <= $signed(k4)*({1'b0, addrW}-{1'b0,Cus_Point4X[13:0]})+{1'b0,Cus_Point4Y[13:0]};
        
        else if ((addrW<Cus_Point6X[13:0]+1'b1)&& (addrW>Cus_Point5X[13:0]))
        dina <= $signed(k5)*({1'b0, addrW}-{1'b0,Cus_Point5X[13:0]})+{1'b0,Cus_Point5Y[13:0]};
        
        else if ((addrW<Cus_Point7X[13:0]+1'b1)&& (addrW>Cus_Point6X[13:0]))
        dina <= $signed(k6)*({1'b0, addrW}-{1'b0,Cus_Point6X[13:0]})+{1'b0,Cus_Point6Y[13:0]};
        
        else if ((addrW<Cus_Point8X[13:0]+1'b1)&& (addrW>Cus_Point7X[13:0]))
        dina <= $signed(k7)*({1'b0, addrW}-{1'b0,Cus_Point7X[13:0]})+{1'b0,Cus_Point7Y[13:0]};
        
        else
        dina <= 0;
    end
    
    
    
    
    
    assign addr_Write = addrW;
    assign data_Wirte = dina;
    
    
    divider divider1(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point2X-Cus_Point1X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point2Y-Cus_Point1Y),
    .m_axis_dout_tvalid      (dout_tvalid1),
    .m_axis_dout_tdata       (dout_tdata1)
    );
    
    divider divider2(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point3X-Cus_Point2X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point3Y-Cus_Point2Y),
    .m_axis_dout_tvalid      (dout_tvalid2),
    .m_axis_dout_tdata       (dout_tdata2)
    );
    
    divider divider3(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point4X-Cus_Point3X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point4Y-Cus_Point3Y),
    .m_axis_dout_tvalid      (dout_tvalid3),
    .m_axis_dout_tdata       (dout_tdata3)
    );
    
    divider divider4(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point5X-Cus_Point4X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point5Y-Cus_Point4Y),
    .m_axis_dout_tvalid      (dout_tvalid4),
    .m_axis_dout_tdata       (dout_tdata4)
    );
    
    divider divider5(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point6X-Cus_Point5X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point6Y-Cus_Point5Y),
    .m_axis_dout_tvalid      (dout_tvalid5),
    .m_axis_dout_tdata       (dout_tdata5)
    );
    
    divider divider6(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point7X-Cus_Point6X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point7Y-Cus_Point6Y),
    .m_axis_dout_tvalid      (dout_tvalid6),
    .m_axis_dout_tdata       (dout_tdata6)
    );
    
    divider divider7(
    .aclk                    (clka),
    .s_axis_divisor_tvalid   (1'b1),
    .s_axis_divisor_tdata    (Cus_Point8X-Cus_Point7X),
    .s_axis_dividend_tvalid  (1'b1),
    .s_axis_dividend_tdata   (Cus_Point8Y-Cus_Point7Y),
    .m_axis_dout_tvalid      (dout_tvalid7),
    .m_axis_dout_tdata       (dout_tdata7)
    );
    
    
    Cus_RAM Cus_RAM(
    .clk(clka),
    .a(addr_Write),
    .d(data_Wirte),
    .we(1'b1),
    .dpo(douta),
    .dpra(addr_Read)
    );
endmodule
