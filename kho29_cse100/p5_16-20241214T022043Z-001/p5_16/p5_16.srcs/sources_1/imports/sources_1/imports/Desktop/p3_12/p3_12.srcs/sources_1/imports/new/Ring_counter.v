`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:09:55 PM
// Design Name: 
// Module Name: Ring_counter
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


module Ring_counter(
    output [3:0] out,
    input adv,
    input clk
    );
    wire [3:0] q;
    
    FDRE #(.INIT(1'b1) ) ff_0 (.C(clk), .R(1'b0), .CE(adv), .D(q[3]), .Q(q[0]));
    FDRE #(.INIT(1'b0) ) ff_1 (.C(clk), .R(1'b0), .CE(adv), .D(q[0]), .Q(q[1]));
    FDRE #(.INIT(1'b0) ) ff_2 (.C(clk), .R(1'b0), .CE(adv), .D(q[1]), .Q(q[2]));
    FDRE #(.INIT(1'b0) ) ff_3 (.C(clk), .R(1'b0), .CE(adv), .D(q[2]), .Q(q[3]));
    
    assign out[3:0] = q[3:0];
endmodule
