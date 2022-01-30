var filterEl = document.getElementById('filter');
        filterEl.focus();

        function filter() {
            var q = filterEl.value.trim().toLowerCase();
            var elems = document.querySelectorAll('tr.file');
            elems.forEach(function(el) {
                if (!q) {
                    el.style.display = '';
                    return;
                }
                var nameEl = el.querySelector('.name');
                var nameVal = nameEl.textContent.trim().toLowerCase();
                if (nameVal.indexOf(q) !== -1) {
                    el.style.display = '';
                } else {
                    el.style.display = 'none';
                }
            });
        }