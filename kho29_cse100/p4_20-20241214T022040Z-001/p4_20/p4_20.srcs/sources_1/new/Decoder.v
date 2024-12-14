`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/07/2023 01:21:31 PM
// Design Name: 
// Module Name: Decoder
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


module Decoder(
    input [3:0] x,
    output [15:0] d
    );
    
    wire [3:0] a, b;
    
    assign b[0] = ~x[0] & ~x[1];
    assign b[1] = x[0] & ~x[1];
    assign b[2] = ~x[0] & x[1];
    assign b[3] = x[0] & x[1];
    
    assign a[0] = ~x[2] & ~x[3];
    assign a[1] = x[2] & ~x[3];
    assign a[2] = ~x[2] & x[3];
    assign a[3] = x[2] & x[3];
    
    assign d[0] = a[0] & b[0];
    assign d[1] = a[0] & b[1];
    assign d[2] = a[0] & b[2];
    assign d[3] = a[0] & b[3];
    
    assign d[4] = a[1] & b[0];
    assign d[5] = a[1] & b[1];
    assign d[6] = a[1] & b[2];
    assign d[7] = a[1] & b[3];
    
    assign d[8] = a[2] & b[0];
    assign d[9] = a[2] & b[1];
    assign d[10] = a[2] & b[2];
    assign d[11] = a[2] & b[3];
    
    assign d[12] = a[3] & b[0];
    assign d[13] = a[3] & b[1];
    assign d[14] = a[3] & b[2];
    assign d[15] = a[3] & b[3];
    
endmodule
