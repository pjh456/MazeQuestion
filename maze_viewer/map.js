const gridContainer = document.getElementById('grid-container');

let isPanning = false;
let startX = 0;
let startY = 0;

let scale = 1;

gridContainer.addEventListener('mousedown', e => {
    isPanning = true;
    startX = e.clientX - gridElem.offsetLeft;
    startY = e.clientY - gridElem.offsetTop;
});

window.addEventListener('mouseup', () => isPanning = false);

window.addEventListener('mousemove', e => {
    if (!isPanning) return;
    gridElem.style.left = `${e.clientX - startX}px`;
    gridElem.style.top = `${e.clientY - startY}px`;
});

gridContainer.addEventListener('wheel', e => {
    e.preventDefault();
    scale += e.deltaY > 0 ? -0.1 : 0.1;
    scale = Math.max(0.3, Math.min(scale, 3));
    gridElem.style.transform = `scale(${scale})`;
});