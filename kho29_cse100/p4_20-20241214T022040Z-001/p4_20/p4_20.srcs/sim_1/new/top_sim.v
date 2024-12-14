`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/10/2023 03:54:29 PM
// Design Name: 
// Module Name: top_sim
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


module top_sim();
    reg clkin, btnR, btnC;
    reg [15:0] sw;
    wire [6:0] seg;
    wire [3:0] an;
    wire [15:0] led;
    
    toplvl UUT(
    .sw(sw),
    .btnR(btnR), 
    .btnC(btnC),
    .clkin(clkin),
    .seg(seg),
    .an(an),
    .led(led)
    ); 
 

   initial    // Clock process for clkin
    begin
        #20
		  clkin = 1'b1;
        forever
        begin
            #50 clkin = ~clkin;
        end
    end 
    
    initial
    begin
    btnC = 1'b0;
    btnR = 1'b0;
    sw = 16'h0000;
    #25000
    btnC = 1'b1;
    #2000
    sw = 16'h0006;
    #20000
    btnC=1'b1;
    sw = 16'h0000;
    
    end
endmodule
