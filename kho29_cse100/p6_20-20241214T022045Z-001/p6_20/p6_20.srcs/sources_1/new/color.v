`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/28/2023 12:27:32 PM
// Design Name: 
// Module Name: color
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


module color(
    input [15:0] y,
    input [15:0] x,
    input player_cord,
    input ship1,
    input ship2,
    input ship3,
    input ship4,
    input ship5,
    input slug1,
    input slug2,
    input slug3,
    input slug4,
    input slug5,
    input showship1,
    input showship2,
    input showship3,
    input showship4,
    input showship5,
    input showslug1,
    input showslug2,
    input showslug3,
    input showslug4,
    input showslug5,
    input flashplayer1,
    input flashborder1,
    input flashplayer2,
    input flashborder2,
    input flashplayer3,
    input flashborder3,
    input flashplayer4,
    input flashborder4,
    input flashplayer5,
    input flashborder5,
    input flashslug1,
    input flashslug2,
    input flashslug3,
    input flashslug4,
    input flashslug5,
    output [3:0] r,
    output [3:0] g,
    output [3:0] b
    );
    
    wire [3:0] border, grass, ground;
    wire player;
    
    wire [3:0] inactive;
    assign inactive = ({4{(y < 479) & (x < 639)}});
                        //ground                                                                  //red border                                                                                 //grass                     //draw player move player                                                                                                                                                  //ship                                                //slug1                                                                //ship2                                          //slug2                                                         //ship3                                             //slug3                                                                  //ship4                                                //slug4                                                                       //ship5                                      //slug5
    assign r = (inactive & ground & 4'b1110) | (inactive & border & 4'b1111 & ~{4{flashborder1}} & ~{4{flashborder2}} & ~{4{flashborder3}} & ~{4{flashborder4}} & ~{4{flashborder5}}) | (inactive & grass & 4'b0000) | (inactive & {4{player_cord}} & 4'b1111 & (~{4{flashplayer1}} & ~{4{flashplayer2}} & ~{4{flashplayer3}} & ~{4{flashplayer4}} & ~{4{flashplayer5}})) | (inactive & {4{ship1}} & 4'b0000 & {4{showship1}}) | (inactive & {4{slug1}} & 4'b1111 & {4{showslug1}} & ~{4{flashslug1}}) | (inactive & {4{ship2}} & 4'b0000 & {4{showship2}}) | (inactive & {4{slug2}} & 4'b1111 & {4{showslug2}} & ~{4{flashslug2}}) | (inactive & {4{ship3}} & 4'b0000 & {4{showship3}}) | (inactive & {4{slug3}} & 4'b1111 & {4{showslug3}} & ~{4{flashslug3}}) | (inactive & {4{ship4}} & 4'b0000 & {4{showship4}}) | (inactive & {4{slug4}} & 4'b1111 & {4{showslug4}} & ~{4{flashslug4}}) | (inactive & {4{ship5}} & 4'b0000 & {4{showship5}}) | (inactive & {4{slug5}} & 4'b1111 & {4{showslug5}} & ~{4{flashslug5}});
    assign g = (inactive & ground & 4'b0111) | (inactive & border & 4'b0000 & ~{4{flashborder1}} & ~{4{flashborder2}} & ~{4{flashborder3}} & ~{4{flashborder4}} & ~{4{flashborder5}}) | (inactive & grass & 4'b1111) | (inactive & {4{player_cord}} & 4'b1111 & (~{4{flashplayer1}} & ~{4{flashplayer2}} & ~{4{flashplayer3}} & ~{4{flashplayer4}} & ~{4{flashplayer5}})) | (inactive & {4{ship1}} & 4'b0000 & {4{showship1}}) | (inactive & {4{slug1}} & 4'b0101 & {4{showslug1}} & ~{4{flashslug1}}) | (inactive & {4{ship2}} & 4'b0000 & {4{showship2}}) | (inactive & {4{slug2}} & 4'b0101 & {4{showslug2}} & ~{4{flashslug2}}) | (inactive & {4{ship3}} & 4'b0000 & {4{showship3}}) | (inactive & {4{slug3}} & 4'b0101 & {4{showslug3}} & ~{4{flashslug3}}) | (inactive & {4{ship4}} & 4'b0000 & {4{showship4}}) | (inactive & {4{slug4}} & 4'b0101 & {4{showslug4}} & ~{4{flashslug4}}) | (inactive & {4{ship5}} & 4'b0000 & {4{showship5}}) | (inactive & {4{slug5}} & 4'b0101 & {4{showslug5}} & ~{4{flashslug5}});
    assign b = (inactive & ground & 4'b0000) | (inactive & border & 4'b0000 & ~{4{flashborder1}} & ~{4{flashborder2}} & ~{4{flashborder3}} & ~{4{flashborder4}} & ~{4{flashborder5}}) | (inactive & grass & 4'b0000) | (inactive & {4{player_cord}} & 4'b0000 & (~{4{flashplayer1}} & ~{4{flashplayer2}} & ~{4{flashplayer3}} & ~{4{flashplayer4}} & ~{4{flashplayer5}})) | (inactive & {4{ship1}} & 4'b1111 & {4{showship1}}) | (inactive & {4{slug1}} & 4'b1111 & {4{showslug1}} & ~{4{flashslug1}}) | (inactive & {4{ship2}} & 4'b1111 & {4{showship2}}) | (inactive & {4{slug2}} & 4'b1111 & {4{showslug2}} & ~{4{flashslug2}}) | (inactive & {4{ship3}} & 4'b1111 & {4{showship3}}) | (inactive & {4{slug3}} & 4'b1111 & {4{showslug3}} & ~{4{flashslug3}}) | (inactive & {4{ship4}} & 4'b1111 & {4{showship4}}) | (inactive & {4{slug4}} & 4'b1111 & {4{showslug4}} & ~{4{flashslug4}}) | (inactive & {4{ship5}} & 4'b1111 & {4{showship5}}) | (inactive & {4{slug5}} & 4'b1111 & {4{showslug5}} & ~{4{flashslug5}});
    
    assign border = ({4{(x < 8 | (x < 639 & x > 629)) | (y < 8 | (y < 479 & y > 470))}});
    assign grass = ({4{(x > 7 & x < 630) & (y >= 412 & y <= 420)}});
    assign ground = ({4{(x > 7 & x < 630) & (y > 420 & y < 471)}});
    //assign player = (y >= 395) & (y <= 411) & (x >= 294) & (x <= 310);
//    assign ground = ({4{}})
endmodule
