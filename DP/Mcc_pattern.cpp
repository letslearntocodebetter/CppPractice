Given index left and right
you chose one k

left <= k <== right
break left, k, k+1,right

and see the maximum number of

you will get the answers and get the max of min of the k

solve(int arr[], int left, int right) {

// base codition for invalid 

 if (left > right) { return 0;}


// it would depend if k starts from left. left + 1 and eds with right or right -1
for ((int k=left; k < right ; k++)) {

    // calculate the temperator answer

    tempanswer = solve(left, k) Operation solve(k+1, right);

    answ = Function(temporaryAnswer)
    Fuction = max, min or any other opration


}
}