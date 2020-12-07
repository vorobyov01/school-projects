function getArrayOfBits() {
    var array = [];
    for (var i = 0; i < 8; i++) {
        array.push(parseInt(document.getElementById("b" + i).innerHTML, 10));
    }
    return array;
}
function getDecimal() {
    array = getArrayOfBits();
    var sum = 0;
    var calc = "";
    for (var i = 0; i < array.length; i++) {
        sum += array[i]*Math.pow(2, i);
    }
    var isFerstDigit = false;
    for (var i = array.length-1; i >= 0 ; i--) {
        if(array[i] == "1") isFerstDigit = true;
        if(isFerstDigit) {
            calc += "<span style='color:" + ((array[i] == 1)? "#e8308c" : "gray") + "'>";
            calc += array[i];
            calc += "</span>";
            calc += " &#8901; <span style='color:gray;'>2<sup>";
            calc += i;
            calc += "</sup></span> ";
            if (i != 0) calc += "+ ";
        }
    }
    document.getElementById("calc").innerHTML = calc;
    document.getElementById("result").innerHTML = sum.toString();
}
function changeBit(bit) {
    element = document.getElementById("b" + bit);
    if (element.innerHTML == "0") {
        element.innerHTML = "1";
        element.style.color = "#e8308c";
    } else {
        element.innerHTML = "0";
        element.style.color = "#3080e8";
    }
    getDecimal();
}

// function calculate() {
//     array = getNumber();
//     var sum = 0;
//     var calc = "";
//     for (var i = 0; i < array.length; i++) {
//         sum += array[i]*Math.pow(2, i);
//     }
//     var isFerstDigit = false;
//     for (var i = array.length-1; i >= 0 ; i--) {
//         if(array[i] == "1") isFerstDigit = true;
//         if(isFerstDigit) {
//             calc += "<span style='color:" + ((array[i] == 1)? "#e8308c" : "gray") + "'>";
//             calc += array[i];
//             calc += "</span>";
//             calc += " &#8901; <span style='color:gray;'>2<sup>";
//             calc += i;
//             calc += "</sup></span> ";
//             if (i != 0) calc += "+ ";
//         }
//     }
//     document.getElementById("calc").innerHTML = calc;
//     document.getElementById("result").innerHTML = sum.toString();
// }

// function changeBit(bit) {
//     element = document.getElementById("b" + bit);
//     if (element.innerHTML == "0") {
//         element.innerHTML = "1";
//         element.style.color = "#e8308c";
//     } else {
//         element.innerHTML = "0";
//         element.style.color = "#3080e8";
//     }
//     calculate();
// }
