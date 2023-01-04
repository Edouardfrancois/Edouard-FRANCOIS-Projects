var n = 0;

function render() {

    var title = React.createElement('h1', {}, 'Bonjour tous le monde', React.createElement('span', {}, n));
    ReactDOM.render(title, document.querySelector('#app'));
}

render();

window.setInterval(function () {
    n++;
    render();
}, 50);