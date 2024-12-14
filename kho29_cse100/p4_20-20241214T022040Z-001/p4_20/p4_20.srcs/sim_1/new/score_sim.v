`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/12/2023 04:05:30 PM
// Design Name: 
// Module Name: score_sim
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


module score_sim(
    );
    reg clk, Up,Dw,LD;
    reg [15:0] Din;
    wire [15:0] Q;
    wire UTC, DTC;
    
    score_counter UUT(
    .clk(clk),
    .Up(Up),
    .Dw(Dw),
    .LD(LD),
    .Din(Din),
    .Q(Q),
    .UTC(UTC),
    .DTC(DTC)
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
    Up=0;
    LD=0;
    Dw=1;
    Din = 16'b0;
    #25000
    ;
    end
    
endmodule
