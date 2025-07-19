


document.addEventListener("DOMContentLoaded", () => {
    const button = document.getElementById("menu1");
    const submenu = document.getElementById("submenu1");

    button.addEventListener("click", () => {
        submenu.classList.toggle("hidden");
    });

    const input = document.getElementById("add_vertex");
    const inputs = document.getElementById("inputs");

    input.addEventListener("click", () => {
        inputs.classList.toggle("hidden");
        submenu.classList.add("hidden");
    });

    const confirm_button = document.getElementById("confirm_text");
    const input_field = document.getElementById("input_menu");

    confirm_button.addEventListener("click", () => {
        const text = input_field.value.trim();
        if(text){
            input_field.Value = "";
            inputs.classList.add("hidden");
        }
    });

});



