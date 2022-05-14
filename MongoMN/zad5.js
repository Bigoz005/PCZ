//zad 5

//lista adresów ze Słowacji
db.customers.aggregate()
	.match({"address.country": "Slovak Republic")
	.unwind("$address")
	.project({"address.street": 1, "address.number": 1, "address.city": 1, "address.country": 0})
	
//ilość wypożyczonych gier każdego wypożyczenia posortowane po rosnąco
db.borrows.aggregate()
  .unwind("$borrowedGames")
  .group({
    _id: "$borrowedGames.game.name",
    borrowedAmount: { $size: "$borrowedGames" },
  })
  .sort({ "borrowedAmount": 1 })