// Predefined list of registered users
const users = [
  { email: "MARINE@gmail.com", password: "12345" },
  { email: "hunar@gmail.com", password: "654321" },
  { email: "yachna3@gmail.com", password: "123456" },
  { email: "ishika@gmail.com", password: "67890" }
];

// Form submission handler
document.getElementById("loginForm").addEventListener("submit", function(event) {
  event.preventDefault();
  const email = document.getElementById("logemail").value;
  const password = document.getElementById("logpass").value;

  const user = users.find(user => user.email === email && user.password === password);

  if (user) {
    const customAlert = document.getElementById("custom-alert");
    const alertText = document.getElementById("alert-text");

    // Set alert text
    alertText.textContent = "Login successful! Redirecting to dashboard...";

    // Show the alert
    customAlert.classList.remove("hidden");
    customAlert.classList.add("visible");

    // Redirect after a delay
    setTimeout(() => {
      customAlert.classList.remove("visible");
      customAlert.classList.add("hidden");
      window.location.href = "dashboard.html";
    }, 3000); // 3 seconds delay
  } else {
    alert("Invalid email or password. Please try again.");
  }
});