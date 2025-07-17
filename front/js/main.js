

document.addEventListener("DOMContentLoaded", () => {
    const button = document.getElementById("menu1");
    const submenu = document.getElementById("submenu1");

    button.addEventListener("click", () => {
        submenu.classList.toggle("hidden");
    });
});