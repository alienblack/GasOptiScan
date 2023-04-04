pragma solidity 0.4.16;
contract TestLoop {
    function test() returns (uint) {

        uint x=0;
        
        uint q=0;
        uint r=0;
        
        uint t=0;
        uint u=0;
       
        uint i = 4;
        uint j = 12;
        uint k = 2;
        uint l = 33;
        uint m = 3;
        uint n = 10;
        uint p = 30;
        while (i<250){
            
            x = x*i + x;
            i++;
        }

        while (j<259){
            
            x= x*j + x;
            j++;
        }
         while (k<248){
            
            q= q*k + q;
            k++;
        }
         while (l<279){
            
            r= r*l + r;
            l++;
        }
         while (m<249){
            
            x= x*m + x;
            m++;
        }
         while (n<256){
            
            t= t*n + t;
            n++;
        }
         while (p<276){
            
            u= u*p + u;
            p++;
        }
        return x;
    }
}






