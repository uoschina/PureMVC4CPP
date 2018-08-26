#ifndef __SINGLTON_HPP__
#define __SINGLTON_HPP__

template <class T> 
class Singlton
{
    protected:
		Singlton()  {}
    public:
        static T* getInstance() 
        {   
            if (s_ins == 0) 
            { 
                //s_ins = new(s_insbuf)T(); 
                s_ins = new T(); 
            }
            return s_ins; 
        }

        ~Singlton()
        {
            //if (s_ins) { s_ins->~T(); }
        }
    private:
        static T * s_ins ;
        //static char  s_insbuf[sizeof(T)];
};

//template <class T> char Singlton<T>::s_insbuf[sizeof(T)];
template <class T> T* Singlton<T>::s_ins =0; 


#endif // 
