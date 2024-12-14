`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 11:52:38 AM
// Design Name: 
// Module Name: Edge_dect
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


module Edge_dect(
    input x,
    input clk,
    output Z
    );
    wire [1:0] D;
    wire [1:0] Q;
    
    assign D[0] = x;
    assign D[1] = Q[0];  
    
    FDRE #(.INIT(1'b0)) f1 (.C(clk), .R(1'b0), .CE(1'b1), .D(D[0]), .Q(Q[0]));
    FDRE #(.INIT(1'b0)) f2 (.C(clk), .R(1'b0), .CE(1'b1), .D(D[1]), .Q(Q[1]));
    
    assign Z = ~Q[1] & Q[0];
endmodule
