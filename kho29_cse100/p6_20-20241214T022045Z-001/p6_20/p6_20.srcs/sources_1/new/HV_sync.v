`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/24/2023 12:40:40 PM
// Design Name: 
// Module Name: HV_sync
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


module vga(
    input clk,
    input [15:0] h,
    input [15:0] v,
    output H_sync,
    output V_sync

    );

    assign H_sync = ~((h >= 16'd655) & (h <= 16'd750));
    assign V_sync = ~((v >= 16'd489) & (v <= 16'd490)); 
    
endmodule
