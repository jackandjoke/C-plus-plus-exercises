#include<iostream>
#include<string>
#include<istream>
#include<ostream>
#include<fstream>

struct Sales_data;
std::istream & read(std::istream &in, Sales_data &rhs);


//Sales_data defined in chapter 2.6.1
struct Sales_data{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

//    Sales_data() = default;
    Sales_data(const std::string &str): bookNo(str) {}
    Sales_data(const std::string &str, const unsigned &us, const double & p) : bookNo(str),units_sold(us),revenue(us*p) {}
    Sales_data(std::istream &in){read(in,*this);}
    Sales_data() :bookNo(""),units_sold(0),revenue(0) {}

    
    Sales_data & combine(const Sales_data &rhs);
    std::string isbn() const{ return bookNo;}

    Sales_data & operator=(Sales_data rhs){
        bookNo = rhs.bookNo;
        units_sold = rhs.units_sold;
        revenue = rhs.revenue;
        return *this;
    }
};

std::istream& operator >> (std::istream &is, Sales_data &rhs){
    is >> rhs.bookNo >> rhs.units_sold >> rhs.revenue;
    if(!is)
        rhs = Sales_data();
    return is;
}

std::ostream& operator << (std::ostream &os, const Sales_data &rhs){
    os  << rhs.bookNo << " "
        << rhs.units_sold << " "
        << rhs.revenue;
    return os;
}


Sales_data operator+ (const Sales_data &lhs, const Sales_data &rhs){
    Sales_data ret;
    if(lhs.bookNo != rhs.bookNo){
        std::cerr << "Only the same bookNo can be added\n";
        return ret;
    }
    ret.bookNo = lhs.bookNo;
    ret.units_sold = lhs.units_sold + rhs.units_sold;
    ret.revenue = lhs.revenue + rhs.revenue;
    return ret;
}


Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}


Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs; 
    sum.combine(rhs);
    return sum;
}

std::istream & read(std::istream &in, Sales_data &rhs){
    double price;
    in >> rhs.bookNo >> rhs.units_sold >>  price;
    rhs.revenue = rhs.units_sold * price;
    return in;
}

std::ostream & print(std::ostream &os, const Sales_data &rhs){
    os << rhs.isbn() << " " << rhs.units_sold << " "
       << rhs.revenue << std::endl;
    return os;
}





int main(int argc, char *argv[]){
    if(argc != 3){
        std::cout << "Usage: ./8.6 <input_filename> <output_filename>\n";
        return 1;
    }
    std::ifstream ifs(argv[1]);

    if(!ifs){
        std::cerr << "Cannot open file " << argv[1] <<"\n";
        return 1;
    }

    std::ofstream ofs(argv[2],std::ofstream::out);
    if(!ofs){
        std::cerr << "Cannot write file " << argv[2] << "\n";
        return 1;
    }

    Sales_data total(ifs);

    if(ifs){
        Sales_data trans;
        ifs >> trans;
        while(ifs){
            if(trans.isbn() == total.isbn()){
                total.combine(trans);
            }else{
                ofs << total << std::endl;;
                total = trans;
            }
            trans = Sales_data();
            ifs >> trans;
        }
        ofs << total << std::endl;
    }else{
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}
