%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all%
clc      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
coeff1 = 'alpha1';
load(coeff1);
coeff2 = 'alpha2';
load (coeff2);
m_p = 'm_p';
load (m_p);
tauacc = 'tau';
load (tauacc);
h = 5;
iteration = 1;
k = 5;
t = 1:size(c);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
N22 = calculN2(h,taux_acroissement,c);
mat_A = calcul_A(h,mat_p,mat_p,coeffdepot1,N22,iteration);
N11 = calculN1(h,k,mat_p,coeffdepot1,mat_p);
mat_C = calcul_C(h,mat_p,mat_p,c,N11,iteration);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1),clf,plot (t,mat_C),title('dispersion apteres C')

figure(2),clf,plot (t,mat_A),title('dispersion ailees A')
