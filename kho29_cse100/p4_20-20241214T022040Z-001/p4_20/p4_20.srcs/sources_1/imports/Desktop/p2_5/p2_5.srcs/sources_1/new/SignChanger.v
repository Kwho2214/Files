`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/17/2023 12:03:09 PM
// Design Name: 
// Module Name: SignChanger
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


module SignChanger(
    input [7:0] a,
    input sign,
    output [7:0] d,
    output ovfl
    );
    wire [7:0] t0;
    adder8 add1 (.A(~a[7:0]), .B(8'd1), .Cin(1'd0), .S(t0[7:0]), .Cout());
    two_one_Mux t1 (.in0(a[7:0]), .in1(t0[7:0]), .sel(sign), .o(d[7:0]));
    assign ovfl = sign & a[7]&(~a[6])&(~a[5])&(~a[4])&(~a[3])&(~a[2])&(~a[1])&(~a[0]);
    
endmodule
