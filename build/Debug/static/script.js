document.getElementById('testButton').addEventListener('click', function() {
    const result = document.getElementById('result');
    result.textContent = 'Static file serving works! ' + new Date().toLocaleTimeString();
}); 