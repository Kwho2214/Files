`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2023 11:46:36 AM
// Design Name: 
// Module Name: control_logic
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


module control_logic(
    
    input clk,
    input Go,
    input anysw,
    input t4,
    input t2,
    input match,
    input won,
    input lost,
   
    output loadtarget,
    output Rtime,
    output incscore,
    output decscore,
    output showtarget,
    output flashscore,
    output flashled,
    //states
    output [7:0] out
   );
    
    wire [6:0] ps, ns;
    
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clk), .R(1'b0), .CE(1'b1), .D(ns[0]), .Q(ps[0]));  
    FDRE #(.INIT(1'b0)) Q4_FF[6:1] (.C({6{clk}}), .R({6{1'b0}}), .CE({6{1'b1}}), .D(ns[6:1]), .Q(ps[6:1]));
    
    //Idle
    assign ns[0] = ps[0] &(~Go | anysw) | ps[2] & (t4 & ~lost) | ps[4] & (t4 & ~won);
    //play
    assign ns[1] = ps[0] & (Go & ~anysw) | ps[1] & (~t2 & ~anysw);
    assign loadtarget = ps[0] & (Go & ~anysw);
    assign showtarget = ~ps[0];
    //wrong guess
    assign ns[2] = ps[1] & (anysw & ~match | t2 ) | ps[2] & (~t4 & ~match);
    assign decscore = ps[2] | (t2 & ~match & anysw);
    //correct guess -> new score
    assign ns[3] = ps[1] & (anysw & match & ~t2) | (ps[3] & ~t2);
    //new score
    assign ns[4] = ps[3] & (t2 & ~won) | (ps[4] & ~t4);
    assign incscore = ps[3] & (t2 & ~won);
    assign flashscore = (ps[3] & ~t2) | (ps[4] & ~t2);
    //won
    //won and after show for 2 sec and flash new for 2 sec?
    assign ns[5] = ps[4] & (won) | ps[5] & won;
    //lose
    //lose if lost and after 4 sec?
    assign ns[6] = ps[2] & (lost) | ps[6] & lost;
    
    assign flashled = ps[2] & ~t4 & ~match | ps[5] | ps[6];
    assign Rtime = (ps[0] & (~anysw & Go)) | (ps[1] & (anysw & ~match & ~t4)) | (ps[1] & (anysw & match & ~t2));
    
    assign out = ps;

endmodule