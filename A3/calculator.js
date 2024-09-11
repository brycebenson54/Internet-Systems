const results = [];

const resultT_element= document.createElement('table');
const resultHR_element = document.createElement('tr');
const xHC_element = document.createElement('th');
const opHC_element = document.createElement('th');
const yHC_element = document.createElement('th');
const resultHC_element = document.createElement('th');

xHC_element.innerText = 'X';
opHC_element.innerText = 'Operator';
yHC_element.innerText = 'Y';
resultHC_element.innerText = 'Result';

resultHR_element.appendChild(xHC_element);
resultHR_element.appendChild(opHC_element);
resultHR_element.appendChild(yHC_element);
resultHR_element.appendChild(resultHC_element);
resultT_element.appendChild(resultHR_element);
document.body.appendChild(resultT_element);
resultT_element.setAttribute('border', '1');

do {
    let xStr = prompt('Enter The Value Of X:');
    let operator = prompt('Enter Operator (+, -, *, /, %): ');
    let yStr = prompt('Enter The Value Of Y:');
    let isValid = true;
    let result;
    let x = parseInt(xStr);
    let y = parseInt(yStr);

    if (isNaN(x) || isNaN(y)) {
        result = 'Wrong Input Number';
        isValid = false;
    } else {
        switch (operator) {
            case '+':
                result = x + y;
                break;
            case '-':
                result = x - y;
                break;
            case '*':
                result = x * y;
                break;
            case '/':
                result = x / y;
                break;
            case '%':
                result = x % y;
                break;
            default:
                isValid = false;
                result = 'Computation Error';
        }
    }
    let resultR_element = document.createElement('tr');
    let xC_element = document.createElement('td');
    let opC_element = document.createElement('td');
    let yC_element = document.createElement('td');
    let resultC_element = document.createElement('td');

    xC_element.innerText = xStr;
    opC_element.innerText = operator;
    yC_element.innerText = yStr;
    resultC_element.innerText = result;
    
    resultR_element.appendChild(xC_element);
    resultR_element.appendChild(opC_element);
    resultR_element.appendChild(yC_element);
    resultR_element.appendChild(resultC_element);

    opC_element.classList.add('operator');

    resultT_element.appendChild(resultR_element);

    if (isValid) {
        results.push(result);
    }
} while (confirm('Continue?'));

const statT_element = document.createElement('table');
const statHR_element = document.createElement('tr');
const minHC_element = document.createElement('th');
const maxHC_element = document.createElement('th');
const avgHC_element = document.createElement('th');
const totalHC_element = document.createElement('th');

minHC_element.innerText = 'Minimum';
maxHC_element.innerText = 'Maximum';
avgHC_element.innerText = 'Average';
totalHC_element.innerText = 'Total';

statHR_element.appendChild(minHC_element);
statHR_element.appendChild(maxHC_element);
statHR_element.appendChild(avgHC_element);
statHR_element.appendChild(totalHC_element);
statT_element.appendChild(statHR_element);

document.body.appendChild(statT_element);
statT_element.setAttribute('border', '1');
let min = results[0];
let max = results[0];
let total = results[0];

for (let i = 1; i < results.length; i++) {
    if (results[i] < min) {
        min = results[i];
    }

    if (results[i] > max) {
        max = results[i];
    }

    total += results[i];
}

let avg = total / results.length;

const statR_element= document.createElement('tr');
const minC_element = document.createElement('td');
const maxC_element = document.createElement('td');
const avgC_element = document.createElement('td');
const totalC_element = document.createElement('td');

minC_element.innerText = min;
maxC_element.innerText = max;
avgC_element.innerText = avg;
totalC_element.innerText = total;

statR_element.appendChild(minC_element)
statR_element.appendChild(maxC_element);
statR_element.appendChild(avgC_element);
statR_element.appendChild(totalC_element);
statT_element.appendChild(statR_element);