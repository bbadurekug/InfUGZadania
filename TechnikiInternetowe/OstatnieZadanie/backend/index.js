const express = require('express');
const bcrypt = require('bcrypt');
const { PrismaClient } = require('../generated/prisma');

const app = express();
const prisma = new PrismaClient();

app.use(express.json());

let currentUser = null;

app.post('/login', async (req, res) => {

	const { name, password } = req.body;

	try {
		const user = await prisma.user.findUnique({ where: { name } });
		if (!user) {
			return res.status(401).json({ error: 'Nie istnieje taki użytkownik' });
		}

		const valid = await bcrypt.compare(password, user.password_hash);

		if (!valid) {
			return res.status(401).json({ error: 'Niepoprawne haslo' });
		}
			
		currentUser = user;

		res.json({ name: user.name, role: user.role });

	}
	catch (error) {
		console.error(error);
		res.status(500).json({ error: 'Błąd serwera' });
	}
	
});

app.post('/register', async (req, res) => {

	const { name, password } = req.body;
	const hashedPassword = await bcrypt.hash(password, 10);
		
	const existingUser = await prisma.user.findUnique({ where: { name } });

	if (existingUser) {
		return res.status(409).json({ error: 'Istnieje już taki użytkownik' });
	}

	const newUser = await prisma.user.create({
		data: { name, password_hash: hashedPassword, role: 'USER' },
	});

	res.json(newUser);
	
});


app.get('/admin/users', async (req, res) => {

	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const users = await prisma.user.findMany();
	res.json(users);

});

app.post('/admin/users', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const { name, password, role} = req.body;
	const hashedPassword = await bcrypt.hash(password, 10);

	const newUser = await prisma.user.create({
		data: { name, password_hash: hashedPassword, role },
	});

	res.json(newUser);

});

app.put('/admin/users/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	const { name, password, role } = req.body;

	try {
	
		const dataToUpdate = { name, role };

		if (password) {
			dataToUpdate.password_hash = await bcrypy.hash(password, 10);
		}

		const updatedUser = await prisma.user.update({
			where: { id },
			data: dataToUpdate,
		});

		res.json(updatedUser);
		
	}
	catch (error) {
		console.error(error);
		res.status(500).json({ error: 'Błąd przy updatecie' });
		
	}

});

app.delete('/admin/users/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}
	
	await prisma.comment.updateMany({
		where: { userId: parseInt(req.params.id) },
		data: { userId: null }
	});

	await prisma.user.delete({
		where: { id: parseInt(req.params.id) },
	});
	
	res.json({ message: 'Użytkownik usunięty'});
	
});

app.get('/admin/comments', async (req, res) => {

	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const comments = await prisma.comment.findMany({
		include: {
			user: { 
				select: { 
					name: true, 
				}, 
			}	
		},
	});
	res.json(comments);

});

app.post('/admin/comments', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const { content, matchId, userName } = req.body;
	
	try {
		
		const user = await prisma.user.findUnique({
			where: { name: userName }
		});

		if (!user) {
			return res.status(400).json({ error: 'Nie ma takiego użytkownika' });
		}
		
		const newComment = await prisma.comment.create({
			data: {
				content,
				matchId,
				userId: user.id,
			}
		});

		res.json(newComment);

	}
	catch (error) {
		console.error(error);
		res.status(500).json({ error: 'Błąd serwera' });
	}

});

app.put('/admin/comments/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	const { content, matchId, userName } = req.body;
	
	const user = await prisma.user.findUnique({
		where: { name: userName }
	});

	if (!user) {
		return res.status(400).json({ error: 'Nie ma teakiego użytkownika' });
	}

	const updated = await prisma.comment.update({
		where: { id },
		data: { content, 
			matchId,
			userId: user.id,
		},
		include: {
			user: true
		}
	});
	res.json(updated);

});

app.delete('/admin/comments/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	await prisma.comment.delete({
		where: { id },
	});

	res.json({ message: 'Komentarz usunięty'});
	
});

app.get('/admin/players', async (req, res) => {

	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const players = await prisma.player.findMany({
		include: {
			team: { 
				select: { 
					name:true, 
				}, 
			},
		},
	});
	res.json(players);

});

app.post('/admin/players', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const { firstName, lastName, foot, teamName } = req.body;
	
	try {
		
		const team = await prisma.team.findUnique({
			where: { name: teamName }
		});

		if (!team) {
			return res.status(400).json({ error: 'Nie ma takiej drużyny' });
		}
		
		const newPlayer = await prisma.player.create({
			data: {
				firstName,
				lastName,
				foot,
				teamId: team.id
			}
		});

		res.json(newPlayer);

	}
	catch (error) {
		console.error(error);
		res.status(500).json({ error: 'Błąd serwera' });
	}

});

app.put('/admin/players/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	const { firstName, lastName, foot, teamName } = req.body;
	
	const team = await prisma.team.findUnique({
		where: { name: teamName }
	});

	if (!team) {
		return res.status(400).json({ error: 'Nie ma teakiej drużyny' });
	}

	const updated = await prisma.player.update({
		where: { id },
		data: { firstName, 
			lastName, 
			foot, 
			teamId: team.id 
		},
		include: {
			team: true
		}
	});
	res.json(updated);

});

app.delete('/admin/players/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	await prisma.player.delete({
		where: { id },
	});

	res.json({ message: 'Zawodnik usunięty'});
	
});

app.get('/admin/teams', async (req, res) => {

	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const teams = await prisma.team.findMany();
	res.json(teams);

});

app.post('/admin/teams', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const { name, shortName } = req.body;

	const newTeam = await prisma.team.create({
		data: { name, shortName },
	});

	res.json(newTeam);

});

app.put('/admin/teams/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	const { name, shortName } = req.body;
	const updated = await prisma.team.update({
		where: { id },
		data: { name, shortName },
	});
	res.json(updated);

});

app.delete('/admin/teams/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	await prisma.team.delete({
		where: { id },
	});

	res.json({ message: 'Drużyna usunięty'});
	
});

app.get('/admin/matches', async (req, res) => {

	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const matches = await prisma.match.findMany({
		include: { 
			hostTeam: { select: { name: true} }, 
			guestTeam: { select: { name: true} } 
		}
	});

	res.json(matches);

});

app.post('/admin/matches', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}
	
	const { date, startTime, endTime, hostTeamName, guestTeamName } = req.body;

	try {
		const hostTeam = await prisma.team.findUnique({ where: { name: hostTeamName } });
		const guestTeam = await prisma.team.findUnique({ where: { name: guestTeamName } });

		if (!hostTeam || !guestTeam) {
			return res.status(400).json({ error: 'Nie poprawna nazwa drużyny'});
		}

		const match = await prisma.match.create({
			data: {
				date,
				startTime,
				endTime,
				hostTeamId: hostTeam.id,
				guestTeamId: guestTeam.id
			}
		});

		res.json(match);
	}
	catch (err) {
		console.error(err);
		res.status(500).json({ error: 'Błąd serwera' });
	}

});

app.put('/admin/matches/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	const { date, startTime, endTime, hostTeamName, guestTeamName } = req.body;
	
	const hostTeam = await prisma.team.findUnique({
		where: { name: hostTeamName }
	});

	const guestTeam = await prisma.team.findUnique({
		where: { name: guestTeamName }
	});

	if (!hostTeam || !guestTeam) {
		return res.status(400).json({ error: 'Nie ma teakiej drużyny' });
	}

	const updated = await prisma.match.update({
		where: { id },
		data: { 
			date,
			startTime,
			endTime, 
			hostTeamId: hostTeam.id, 
			guestTeamId: guestTeam.id 
		},
		include: {
			hostTeam: { select: { name: true} },
			guestTeam: { select: { name: true} }
		}
	});

	res.json(updated);

});

app.delete('/admin/matches/:id', async (req, res) => {
	
	if (!currentUser || currentUser.role !== 'ADMIN') {
		return res.status(403).json({ error: 'Brak dostępu' });
	}

	const id = parseInt(req.params.id);
	await prisma.match.delete({
		where: { id },
	});

	res.json({ message: 'Mecz usunięty'});
	
});

app.get('/matches', async (req, res) => {

	const matches = await prisma.match.findMany({
		include: { 
			hostTeam: { select: { name: true} }, 
			guestTeam: { select: { name: true} } 
		}
	});

	res.json(matches);

});

app.get('/matches/:id', async (req, res) => {
	
	const id = parseInt(req.params.id);

	const match = await prisma.match.findUnique({
		where: { id },
		include: {
			hostTeam: { 
				include: {
					players: true
				},
			},
			guestTeam: { 
				include: {
					players: true	
				},
			},
			comments: {
				include: { user: { select: { name: true } } },
			}
		}
	});

	if (!match) {
		return res.status(400).json({ error: 'Mecz nie został znaleziony' });
	}

	res.json(match);

});

app.post('/matches/:id/comments', async (req, res) => {
	
	const matchId = parseInt(req.params.id);
	const { content } = req.body;
	
	if (!currentUser) {
		return res.status(401).json({ error: 'Nie jesteś zalogowany' });
	}
	
	const comment = await prisma.comment.create({
		data: {
			content: content,
			matchId,
			userId: currentUser.id
		}
	});
	
	res.json(comment);

});

const PORT = 4000;
app.listen(PORT, () => {
	console.log(`Backend działa na http://localhost:${PORT}`);
});
