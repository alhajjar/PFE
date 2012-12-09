function [B] = calculN2(h,taux_acroissement,alpha2)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   for i=1:196
        for  j=1:194
            m(i,j) = (1 - h *(taux_acroissement(i,j) - alpha2(i,j)));
        end
   end

    B = pinv(m);
    
