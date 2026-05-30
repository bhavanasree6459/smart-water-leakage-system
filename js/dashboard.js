window.addEventListener("load", function () {
    const canvas = document.getElementById("myChart");

    new Chart(canvas, {
        type: "bar",
        data: {
            labels: ["Zone 1", "Zone 2", "Zone 3"],
            datasets: [{
                label: "Leak Count",
                data: [3, 1, 4],
                backgroundColor: "blue"
            }]
        }
    });
});