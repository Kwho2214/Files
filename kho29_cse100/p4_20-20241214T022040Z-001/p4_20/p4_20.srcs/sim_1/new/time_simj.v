`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2023 04:31:09 PM
// Design Name: 
// Module Name: time_simj
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


module time_simj(
    );
    reg clk, Up, Dw, R;
    reg [15:0] Din;
    wire [5:0] Q;
    
    time_counter UUT (
    .clk(clk),
    .Up(Up),
    .Dw(Dw),
    .R(R),
    .Din(Din),
    .Q(Q)
    );
    
    initial    // Clock process for clkin
    begin
        #20
		  clk = 1'b1;
        forever
        begin
            #50 clk = ~clk;
        end
    end    
    
    initial
    begin
    Up=1;
    R=0;
    Dw=0;
    Din = 16'b0;
    #25000;
    
    end
    
endmodule
