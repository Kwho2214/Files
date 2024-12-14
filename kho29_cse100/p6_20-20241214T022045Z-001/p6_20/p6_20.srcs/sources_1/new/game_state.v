`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/10/2023 06:57:23 PM
// Design Name: 
// Module Name: game_state
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


module game_state(
    input clk,
    input btnC,
    input freeze,
    input [15:0] x,
    input [15:0] y,
    output Go1,
    output Go2,
    output Go3,
    output Go4,
    output Go5,
    output [15:0] led,
    output game_over
    );
    
    wire [6:0] ps, ns;
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clk), .R(1'b0), .CE(1'b1), .D(ns[0]), .Q(ps[0]));  
    FDRE #(.INIT(1'b0)) Q3_FF[6:1] (.C({6{clk}}), .R({6{1'b0}}), .CE({6{1'b1}}), .D(ns[6:1]), .Q(ps[6:1]));
    
    wire reset_time;
    wire frame;
    assign frame = (x == 700 & y == 500);
    //assign frame =1;
    wire t1;
    wire [15:0] t_out;
    score_counter time_one (.clk(clk), .reset(reset_time), .enable(1'b1), .Up(frame & (ps[1] | ps[2] | ps[3] | ps[4] | ps[5] | ps[6])), .Dw(1'b0), .Din(16'b0), .LD(1'b0), .Q(t_out), .UTC(), .DTC());
    //1sec
    assign t1 = t_out[5] & t_out[4] & t_out[3] & t_out[2] & ~t_out[1] & ~t_out[0];
    
    //idle
    assign ns[0] = ps[0] & ~btnC | ps[6] & ~freeze;
    assign led[0] = ps[0];
    //ship1
    assign ns[1] = ps[0] & (btnC) | ps[1] & (~t1 & ~freeze) | ps[5] & (t1 & ~freeze);
    assign Go1 = ps[1] & t1;
    assign led[1] = ps[1];
    //ship2
    assign ns[2] =  ps[1] & (t1 & ~freeze) | ps[2] & (~t1 & ~freeze); 
    assign Go2 = ps[2] & t1;
    assign led[2] = ps[2];
    //ship3
    assign ns[3] = ps[2] & (t1 & ~freeze) | ps[3] & (~t1 & ~freeze);
    assign Go3 = ps[3] & t1;
    assign led[3] = ps[3];
    //ship4
    assign ns[4] = ps[3] & (t1 & ~freeze) | ps[4] & (~t1 & ~freeze);
    assign Go4 = ps[4] & t1;
    assign led[4] = ps[4];
    //ship5
    assign ns[5] = ps[4] & (t1 & ~freeze) | ps[5] & (~t1 & ~freeze);
    assign Go5 = ps[5] & t1;
    assign led[5] = ps[5];
    //ship5 ps[5] & (t1 & ~freeze) | ps[6] & (~t1 & ~freeze);
    //lost
    assign ns[6] = ps[1] & (~btnC & freeze) | ps[2] & (~btnC & freeze)| ps[3] & (~btnC & freeze)| ps[4] & (~btnC & freeze) | ps[5] & (~btnC & freeze) | ps[6] & freeze;
    
    assign reset_time = ps[0] & btnC | ps[1] & t1 | ps[2] & t1 | ps[3] & t1 | ps[4] & t1 | ps[5] & t1;
    assign game_over = ps[6];
    assign led[6] = ps[6];
    
    
endmodule
