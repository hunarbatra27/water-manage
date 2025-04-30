// script.js
document.getElementById("register-form").addEventListener("submit", function(event) {
    event.preventDefault();

    const username = document.getElementById("username").value;
    const email = document.getElementById("email").value;
    const password = document.getElementById("password").value;

    const data = {
        username: username,
        email: email,
        password: password
    };

    // Send POST request to Flask backend
    fetch("http://127.0.0.1:5000/register", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(data)
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("response-message").textContent = data.message;
        if (data.message === "User registered successfully!") {
            document.getElementById("register-form").reset();
        }
    })
    .catch(error => {
        document.getElementById("response-message").textContent = "Error registering user.";
    });
});