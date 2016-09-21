constexpr int divide(int id) {
    return id>0 ? id+id/divide(id-1) : id;
};
int main(){
    static_assert(divide(4)>0, "error"); //error
}
