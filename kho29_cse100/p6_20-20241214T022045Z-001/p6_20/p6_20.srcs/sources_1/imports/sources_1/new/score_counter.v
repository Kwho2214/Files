`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2023 04:44:44 PM
// Design Name: 
// Module Name: score_counter
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


module score_counter(
    input clk,
    input [15:0] Din,
    input Up,
    input Dw,
    input LD,
    input reset,
    input enable,
    output [15:0] Q,
    output UTC,
    output DTC
    );
    
    wire [3:0] t, z, u, d;
        
    //up logic
    assign t[0] = Up;
    assign t[1] = Up & u[0];
    assign t[2] = u[1] & (Up & u[0]);
    assign t[3] = u[2] & (u[1] & (u[0] & Up)); 
    
    //down logic
    assign z[0] = Dw;
    assign z[1] = d[0] & Dw;
    assign z[2] = d[1] & (Dw & d[0]);
    assign z[3] = d[2] & (d[1] & (d[0] & Dw)); 
    
    Counter_four c0(.clk(clk), .Up(t[0]), .reset(reset), .enable(enable), .Dw(z[0]), .LD(LD), .Din(Din[3:0]), .Q(Q[3:0]), .UTC(u[0]), .DTC(d[0]));
    Counter_four c1(.clk(clk), .Up(t[1]), .reset(reset), .enable(enable), .Dw(z[1]), .LD(LD), .Din(Din[7:4]), .Q(Q[7:4]), .UTC(u[1]), .DTC(d[1]));
    Counter_four c2(.clk(clk), .Up(t[2]), .reset(reset), .enable(enable), .Dw(z[2]), .LD(LD), .Din(Din[11:8]), .Q(Q[11:8]), .UTC(u[2]), .DTC(d[2]));
    Counter_four c3(.clk(clk), .Up(t[3]), .reset(reset), .enable(enable), .Dw(z[3]), .LD(LD), .Din(Din[15:12]), .Q(Q[15:12]), .UTC(u[3]), .DTC(d[3]));
    
    assign UTC = u[0]&u[1]&u[2]&u[3];
    assign DTC = d[0]&d[1]&d[2]&d[3];
endmodule
