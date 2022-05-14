//zad 3

//aktywni klienci
db.customers.find({ isActive: true }); 

//pierwsze wypożyczenie gry
db.borrows.find().sort({ borrowDate: 1 }).limit(1); 

//klienci w wieku 24 lat
db.customers.find({ age: 24 }); 

//klienci posortowani wiekiem malejąco, saldem konta rosnąco
db.customers.find({}).sort( {age : -1, balance: 1}) 

//klienci ze Słowacji lub kobiety
db.customers.find({
	$or: [
	{ "address.country": "Slovak Republic" },
	{ gender: "female" }
	]
});

//klienci, z wieku od 20 do 35 lat
db.customers.find({
  $and: [
    { age: { $gt: 20 } },
    { age: { $lt: 35 } },
  ],
});

//klienci którzy mają conajmniej 40 lat i mają na koncie więcej niż 1000, posortowani wiekiem rosnąco
db.customers.find({
    $and: [
      { age: { $gte: 40 } },
      { balance: { $gt: 1000 } },
    ],
  })
.sort({ age: 1 }); 

//klienci mający więcej niż 20 lat, mający 3 przyjaciół i mieszkający w Słowacji
db.cutomers.find({
  $and: [
    { age: { $gt: 20 } },
    { friends: { $size: 3 } },
	{ "addres.country": "Slovak Republic"},
  ],
});