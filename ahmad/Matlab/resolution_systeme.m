clear all
clc
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mat_p = 'm_p';
load(mat_p);
coeffdepot1 = 'alpha1';
load(coeffdepot1);
N22 = 'N22';
load(N22);
h = 5;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 mat_C = h* (coeffdepot1*N22* mat_p) + mat_p;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 