function [B] = calculN2(h,taux_acroissement,alpha2)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
f = 1;
   for i=1:196
        for  j=1:194
            
            B(1,f) = 1/(1 - h *(taux_acroissement(i,j) - alpha2(i,j)));
f = f+1;
        end
   end

%     B = pinv(m);
end
