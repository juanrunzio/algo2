function agregar_animo() {
    // Agarramos el form para obtener su contenido
    let elementos = document.getElementById("form_animo").elements;
    let dia = elementos.dia.value;
    let animo = elementos.animo.value;

    if (dia < 1 || dia > 31) {
        alert("El día tiene que estar entre 1 y 31");
        return
    };

    if (document.getElementById(`dia_${dia}`)) {
        alert("Ya existe un ánimo cargado para ese día, si quiere cargar uno nuevo, elimine el anterior");
        return
    };
    // Creamos un nuevo elemento
    let nuevo_elemento = document.createElement("li"); // <li></li>

    nuevo_elemento.setAttribute("id", `dia_${dia}`);
    nuevo_elemento.setAttribute("class", "list-group-item")

    if (animo == "muy_bien"){
        nuevo_elemento.classList.add("list-group-item-success")
    } else if (animo == "bien") {
        nuevo_elemento.classList.add("list-group-item-primary")
    } 
    
    let nuevo_dia = document.createElement("div");
    nuevo_dia.setAttribute("class", "col");
    nuevo_dia.append(`Día: ${dia}`);

    let nuevo_animo = document.createElement("div");
    nuevo_animo.setAttribute("class", "col");
    nuevo_animo.append(`Ánimo: ${transformar_animo(animo)}`);

    let nuevo_remover = document.createElement("div");
    nuevo_remover.setAttribute("class", "col");

    let nuevo_boton = document.createElement("button");
    nuevo_boton.setAttribute("class", "btn btn-sm btn-danger")
    nuevo_boton.innerText = "Remover"
    nuevo_boton.onclick = function () { remover_animo(`dia_${dia}`) };

    nuevo_remover.append(nuevo_boton);

    let nueva_row = document.createElement("div");
    nueva_row.setAttribute("class", "row");

    nueva_row.append(nuevo_dia);
    nueva_row.append(nuevo_animo);
    nueva_row.append(nuevo_remover);

    nuevo_elemento.append(nueva_row);

    // Obtenemos el listado de animos cargados
    let animos = document.getElementById("animos_cargados");
    animos.append(nuevo_elemento);
}

function remover_animo(id) {
    document.getElementById(id).remove()
}

function borrar_todo() {
    document.getElementById("animos_cargados").innerHTML = "";
}

function transformar_animo(animo){
    if (animo == "muy_bien"){
        return "😁";
    }
    return animo;
}
