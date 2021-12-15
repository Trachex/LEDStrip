window.onload = () => {
    document.querySelector("#form button").addEventListener("click", send);
}

function send() {
    const ssid = document.querySelector("#form input[name='ssid']").value;
    const pass = document.querySelector("#form input[name='pass']").value;
    if(ssid == "" || pass == "") return alert('No username or password');

    fetch("/wifi/connect", { 
        method: 'POST', 
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({ "workSsid": ssid, "workPass": pass })
    })
    .then((response) => {
        return response.json();
    })
    .then((data) => {
        document.querySelector("#ip").innerHTML = data.ip;
        document.querySelector("#mac").innerHTML = data.mac;
    });
}