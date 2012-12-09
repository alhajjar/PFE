function [mat] = coeff_envol( A, stades, theta)
     a=0.034733;
     a0=1.417143;
     a1=0.048163;
     a2=-0.543663;

   for i=1:196
        for j=1:194
            logN4=exp(a*stades(i,j))/(1+exp(a0+a1*stades(i,j)+a2*log(1+A)));
            phi_alpha2=2/( 1 + exp( - 0.1 * theta(i,j)))- 1;
            mat(i, j) = exp(logN4)*phi_alpha2;
        end
   end
end