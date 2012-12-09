function [alpha2] = coeff_depot2( p, eta)
     a1 = -0.128715;
     a2 = 24.589110;
     a3 = 0.946651;
     a4 = 0.079787;
     a5 = 0.906087;
     k = 7.317821;
    
    for i=1:196
            for j=1:194
              num = (a4*exp(p(i,j))+a5*log(1+p(i,j)));
              den = 1-a1*atan(k*eta(i,j))+exp(a2*(p(i,j)-a3));
              alpha2(i, j) = num/den;
            end
    end
end