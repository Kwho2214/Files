`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/12/2023 02:37:09 PM
// Design Name: 
// Module Name: rand_sim
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


module rand_sim(
    );
    reg clkin;
    wire [7:0] Q;
    
    rand_num UUT(
    .clkin(clkin),
    .Q(Q)
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
    
    
endmodule
