//zad 6

//lista wypożyczeń
function borrowsFun() {
  const borrows = db.borrows.find({});
  if (borrows.length) {
    borrows.forEach((borrow) => {
      const customer = db.customers.findOne({ _id: borrow.userId })
      print(`${customer.name.first} ${customer.name.last}, ${borrow.borrowDate.toString()} ${borrow.borrowedGames} );
    });
  }
}